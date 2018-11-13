var User = require('./../models').User;

module.exports.create = function(req, res, next) {
  User.authenticate(req.body.email, req.body.password, function(err, user) {
    if (err) return next(err);

    if (user) {
      req.session.userId = user.email;
      var redirect = (req.query.redirect != null ? req.query.redirect : '/account');
      res.redirect(redirect);
    } else {
      res.status(401).render('login');
    }
  });
};

module.exports.show = function(req, res, next) {
  res.render('login');
};
