// Load required packages
var passport = require('passport');
var BasicStrategy = require('passport-http').BasicStrategy;
var BearerStrategy = require('passport-http-bearer').Strategy
var User = require('../models/user');
var Client = require('../models/client');
var Token = require('../models/token');

passport.use(new BasicStrategy(
  function(username, password, callback) {
    console.log('1.controller auth BasicStrategy : ', username, password)
    User.find({}, function (err, users) {
      if (err) { return callback(err); }
      console.log('2.controller auth BasicStrategy find users : ', users)
    })
    User.findOne({ username: username }, function (err, user) {
      if (err) { return callback(err); }
      console.log('2.controller auth BasicStrategy findOne user : ', user)
      // No user found with that username
      if (!user) { return callback(null, false); }

      // Make sure the password is correct
      user.verifyPassword(password, function(err, isMatch) {
        if (err) { return callback(err); }
        console.log('3.controller auth BasicStrategy verifyPassword : ', isMatch)
        // Password did not match
        if (!isMatch) { return callback(null, false); }

        // Success
        return callback(null, user);
      });
    });
  }
));

passport.use('client-basic', new BasicStrategy(
  function(username, password, callback) {
    console.log('1.controller auth client-basic : ', username, password)
    Client.find({}, function (err, clients) {
      console.log('2.controller auth client-basic find clients : ', clients)
      if (err) { return callback(err); }
    })
    Client.findOne({ id: username }, function (err, client) {
      if (err) { return callback(err); }
      console.log('3.controller auth client-basic findOne client : ', client)
      // No client found with that id or bad password
      if (!client || client.secret !== password) { return callback(null, false); }

      // Success
      return callback(null, client);
    });
  }
));

passport.use(new BearerStrategy(
  function(accessToken, callback) {
    console.log('1.controller auth BearerStrategy : ', accessToken)
    Token.findOne({value: accessToken }, function (err, token) {
      if (err) { return callback(err); }
      console.log('2.controller auth BearerStrategy findOne token : ', token)
      // No token found
      if (!token) { return callback(null, false); }

      User.findOne({ _id: token.userId }, function (err, user) {
        if (err) { return callback(err); }
        console.log('3.controller auth BearerStrategy findOne user : ', user)
        // No user found
        if (!user) { return callback(null, false); }

        // Simple example with no scope
        callback(null, user, { scope: '*' });
      });
    });
  }
));

exports.isAuthenticated = passport.authenticate(['basic', 'bearer'], { session : false });
exports.isClientAuthenticated = passport.authenticate('client-basic', { session : false });
exports.isBearerAuthenticated = passport.authenticate('bearer', { session: false });









