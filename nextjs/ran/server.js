/* eslint-disable no-console */
const express = require('express');
const next = require('next');
const compression = require('compression');
const LRUCache = require('lru-cache');
const path = require('path');
const fs = require('fs');
const cors = require('cors');
const helmet = require('helmet');
const Gun = require('gun');
require('dotenv').config();

const router = require('./routes');
const logger = require('./server/logger');

const isDev = process.env.NODE_ENV !== 'production';
const isProd = !isDev;
const ngrok = isDev && process.env.ENABLE_TUNNEL ? require('ngrok') : null;

const customHost = process.env.HOST;
const host = customHost || null;
const prettyHost = customHost || 'localhost';
const port = parseInt(process.env.PORT, 10) || 3000;

const app = next({ dev: isDev });
const handle = app.getRequestHandler();

const ssrCache = new LRUCache({
  max: 100,
  maxAge: 3600 // 1 hour
});

const buildStats = isProd
  ? JSON.parse(fs.readFileSync('./.next/build-stats.json', 'utf8').toString())
  : null;

const buildId = isProd
  ? fs.readFileSync('./.next/BUILD_ID', 'utf8').toString()
  : null;

/*
 * NB: make sure to modify this to take into account anything that should trigger
 * an immediate page change (e.g a locale stored in req.session)
 */
const getCacheKey = function getCacheKey(req) {
  return `${req.url}`;
};

const renderAndCache = function renderAndCache(
  req,
  res,
  pagePath,
  queryParams
) {
  const key = getCacheKey(req);

  if (ssrCache.has(key) && !isDev) {
    console.log(`CACHE HIT: ${key}`);
    res.send(ssrCache.get(key));
    return;
  }

  app
    .renderToHTML(req, res, pagePath, queryParams)
    .then(html => {
      // Let's cache this page
      if (!isDev) {
        console.log(`CACHE MISS: ${key}`);
        ssrCache.set(key, html);
      }

      res.send(html);
    })
    .catch(err => {
      app.renderError(err, req, res, pagePath, queryParams);
    });
};

const routerHandler = router.getRequestHandler(
  app,
  ({ req, res, route, query }) => {
    renderAndCache(req, res, route.page, query);
  }
);

app.prepare().then(() => {
  const server = express();

  const gunOptions = {
    file: 'data.json',
    web: server,
    s3: {
        key: '', // AWS Access Key
        secret: '', // AWS Secret Token
        bucket: '' // The bucket you want to save into
    }
  };

  const gun = Gun(gunOptions);

  server.use(compression({ threshold: 0 }));
  server.use(
    cors({
      origin:
        prettyHost.indexOf('http') !== -1 ? prettyHost : `http://${prettyHost}`,
      credentials: true
    })
  );
  server.use(Gun.serve);
  server.use(helmet());
  server.use(routerHandler);

  server.get(`/favicon.ico`, (req, res) =>
    app.serveStatic(req, res, path.resolve('./static/icons/favicon.ico'))
  );

  server.get('/sw.js', (req, res) =>
    app.serveStatic(req, res, path.resolve('./.next/sw.js'))
  );

  server.get('/manifest.html', (req, res) =>
    app.serveStatic(req, res, path.resolve('./.next/manifest.html'))
  );

  server.get('/manifest.appcache', (req, res) =>
    app.serveStatic(req, res, path.resolve('./.next/manifest.appcache'))
  );

  if (isProd) {
    server.get('/_next/-/app.js', (req, res) =>
      app.serveStatic(req, res, path.resolve('./.next/app.js'))
    );

    const hash = buildStats['app.js'] ? buildStats['app.js'].hash : buildId;

    server.get(`/_next/${hash}/app.js`, (req, res) =>
      app.serveStatic(req, res, path.resolve('./.next/app.js'))
    );
  }

  server.get('*', (req, res) => handle(req, res));

  server.listen(port, host, err => {
    if (err) {
      return logger.error(err.message);
    }

    if (ngrok) {
      ngrok.connect(port, (innerErr, url) => {
        if (innerErr) {
          return logger.error(innerErr);
        }

        logger.appStarted(port, prettyHost, url);
      });
    } else {
      logger.appStarted(port, prettyHost);
    }
  });
});
