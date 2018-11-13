"use strict";

Object.defineProperty(exports, "__esModule", {
      value: true
});

var _graphqlTools = require("graphql-tools");

var _resolvers = require("./resolvers");

var _resolvers2 = _interopRequireDefault(_resolvers);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var schema = "\ntype Author {\n      id: Int! # the ! means that every author object _must_ have an id\n            firstName: String\n              lastName: String\n                posts: [Post] # the list of Posts by this author\n}\ntype Post {\n      id: Int!\n            title: String\n              author: Author\n                votes: Int\n}\n# the schema allows the following query:\ntype Query {\n      posts: [Post]\n            author(id: Int!): Author\n}\n# this schema allows the following mutation:\ntype Mutation {\n      upvotePost (\n                  postId: Int!\n                    ): Post\n}\n";

exports.default = (0, _graphqlTools.makeExecutableSchema)({
      typeDefs: schema,
      resolvers: _resolvers2.default
});