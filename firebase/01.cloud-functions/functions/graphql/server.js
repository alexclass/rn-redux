"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _bodyParser = require("body-parser");

var _bodyParser2 = _interopRequireDefault(_bodyParser);

var _express = require("express");

var _express2 = _interopRequireDefault(_express);

var _graphqlServerExpress = require("graphql-server-express");

var _schema = require("./data/schema");

var _schema2 = _interopRequireDefault(_schema);

var _schemaPrinter = require("graphql/utilities/schemaPrinter");

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var setupGraphQLServer = function setupGraphQLServer() {
  // setup server
  var graphQLServer = (0, _express2.default)();

  // /api/graphql
  graphQLServer.use("/graphql", _bodyParser2.default.json(), (0, _graphqlServerExpress.graphqlExpress)({ schema: _schema2.default, context: {} }));

  // /api/graphiql
  graphQLServer.use("/graphiql", (0, _graphqlServerExpress.graphiqlExpress)({ endpointURL: "/api/graphql" }));

  // /api/schema
  graphQLServer.use("/schema", function (req, res) {
    res.set("Content-Type", "text/plain");
    res.send((0, _schemaPrinter.printSchema)(_schema2.default));
  });

  return graphQLServer;
};

exports.default = setupGraphQLServer;