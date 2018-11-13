// Load required packages
var User = require('../models/user');

// Create endpoint /api/users for POST
exports.postUsers = function(req, res) {
  const userOptions = {
    username: req.body.username,
    password: req.body.password
  }
  var user = new User(userOptions);
  console.log('1.controller user : ', userOptions)
  user.save(function(err) {
    console.log('1.controller user save : ', user)
    if (err)
      return res.send(err);

    res.json({ message: 'New beer drinker added to the locker room!' });
  });
};

// Create endpoint /api/users for GET
exports.getUsers = function(req, res) {
  User.find(function(err, users) {
    console.log('1.controller user getUsers : ', users)
    if (err)
      return res.send(err);

    res.json(users);
  });
};