// Load required packages
var mongoose = require('mongoose');
var bcrypt = require('bcrypt-nodejs');
require('debug')('models:user');

// Define our user schema
var UserSchema = new mongoose.Schema({
  username: {
    type: String,
    unique: true,
    required: true
  },
  password: {
    type: String,
    required: true
  }
});

// Execute before each user.save() call
UserSchema.pre('save', function(callback) {
  var user = this;
  console.log('1.models user pre save : ', user)
  // Break out if the password hasn't changed
  if (!user.isModified('password')) return callback();

  // Password changed so we need to hash it
  bcrypt.genSalt(5, function(err, salt) {
    console.log('2.models user pre save genSalt : ', salt)
    if (err) return callback(err);

    bcrypt.hash(user.password, salt, null, function(err, hash) {
      console.log('3.models user pre save hash : ', hash)
      if (err) return callback(err);
      user.password = hash;
      callback();
    });
  });
});

UserSchema.methods.verifyPassword = function(password, cb) {
  bcrypt.compare(password, this.password, function(err, isMatch) {
    console.log('1.models user verifyPassword : ', isMatch)
    if (err) return cb(err);
    cb(null, isMatch);
  });
};

// Export the Mongoose model
module.exports = mongoose.model('User', UserSchema);