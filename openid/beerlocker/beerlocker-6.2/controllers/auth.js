// Load required packages
var passport = require('passport');
var BasicStrategy = require('passport-http').BasicStrategy;
var DigestStrategy = require('passport-http').DigestStrategy;
var LocalStrategy = require('passport-local').Strategy;
var BearerStrategy = require('passport-http-bearer').Strategy;
var User = require('../models/user');
var Client = require('../models/client');
var Token = require('../models/token');
require('debug')('controller:auth');

passport.use(new BasicStrategy(
  function(username, password, callback) {
    console.log('1.controller auth BasicStrategy : ', username, password)
    User.find({ }, function (err, users) {
      console.log('2.controller auth BasicStrategy find : ', users)
      if (err) { return callback(err); }
    })
    User.findOne({ username: username }, function (err, user) {
      console.log('3.controller auth BasicStrategy findOne : ', user)
      if (err) { return callback(err); }

      // No user found with that username
      if (!user) { return callback(null, false); }

      // Make sure the password is correct
      user.verifyPassword(password, function(err, isMatch) {
        console.log('4.controller auth BasicStrategy verifyPassword : ', isMatch)
        if (err) { return callback(err); }

        // Password did not match
        if (!isMatch) { return callback(null, false); }

        // Success
        return callback(null, user);
      });
    });
  }
));

passport.use(new DigestStrategy(
  { algorithm: 'MD5', qop: 'auth' },
  function(username, callback) {
    User.find({ }, function (err, users) {
      console.log('1.controller auth DigestStrategy find users : ', users)
      if (err) { return callback(err); }
    })
    User.findOne({ username: username }, function (err, user) {
      console.log('2.controller auth DigestStrategy findOne user : ', user)
      if (err) { return callback(err); }

      // No user found with that username
      if (!user) { return callback(null, false); }

      // Success
      return callback(null, user, user.password);
    });
  },
  function(params, callback) {
    // validate nonces as necessary
    let nonces = true
    console.log('3.controller auth DigestStrategy validate nonces : ', nonces, params)
    callback(null, nonces);
  }
));

passport.use(new LocalStrategy({
    usernameField: 'email',
    passwordField: 'pass'
  },
  function(username, password, callback) {
    console.log('1.controller auth LocalStrategy : ', username, password)
    User.find({ }, function (err, users) {
      console.log('2.controller auth LocalStrategy find users: ', users)
      if (err) { return callback(err); }
    })
    User.findOne({ username: username }, function (err, user) {
      console.log('3.controller auth LocalStrategy findOne user : ', user)
      if (err) { return callback(err); }

      // No user found with that username
      if (!user) { return callback(null, false); }

      // Make sure the password is correct
      user.verifyPassword(password, function(err, isMatch) {
        console.log('4.controller auth LocalStrategy verifyPassword : ', isMatch)
        if (err) { return callback(err); }

        // Password did not match
        if (!isMatch) { return callback(null, false); }

        // Success
        console.log('5.controller auth LocalStrategy verifyPassword success : ', user)
        return callback(null, user);
      });
    });
  }
));

passport.use('client-basic', new BasicStrategy(
  function(username, password, callback) {
    console.log('1.controller auth client-basic : ', username, password)
    Client.find({ }, function (err, clients) {
      console.log('2.controller auth client-basic find clients : ', clients)
      if (err) { return callback(err); }
    })
    Client.findOne({ id: username }, function (err, client) {
      console.log('3.controller auth client-basic findOne client : ', client)
      if (err) { return callback(err); }

      // No client found with that id or bad password
      if (!client || client.secret !== password) { return callback(null, false); }

      // Success
      console.log('4.controller auth client-basic success : ', client)
      return callback(null, client);
    });
  }
));

passport.use(new BearerStrategy(
  function(accessToken, callback) {
    console.log('1.controller auth BearerStrategy : ', accessToken)
    Token.find({ }, function (err, tokens) {
      console.log('2.controller auth BearerStrategy find tokens : ', tokens)
      if (err) { return callback(err); }
    })
    Token.findOne({value: accessToken }, function (err, token) {
      console.log('3.controller auth BearerStrategy findOne token : ', token)
      if (err) { return callback(err); }

      // No token found
      if (!token) { return callback(null, false); }
      User.find({ }, function (err, users) {
        console.log('4.controller auth BearerStrategy find users : ', users)
        if (err) { return callback(err); }
      })
      User.findOne({ _id: token.userId }, function (err, user) {
        console.log('5.controller auth BearerStrategy findOne user : ', user)
        if (err) { return callback(err); }

        // No user found
        if (!user) { return callback(null, false); }

        // Simple example with no scope
        const scope = { scope: '*' }
        console.log('6.controller auth BearerStrategy success : ', user, scope)
        callback(null, user, scope);
      });
    });
  }
));

exports.isAuthenticated = passport.authenticate(['local', 'bearer'], { session : false });
exports.isClientAuthenticated = passport.authenticate('client-basic', { session : false });
exports.isBearerAuthenticated = passport.authenticate('bearer', { session: false });