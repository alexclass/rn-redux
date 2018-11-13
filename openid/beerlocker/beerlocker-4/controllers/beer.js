// Load required packages
var Beer = require('../models/beer');

// Create endpoint /api/beers for POST
exports.postBeers = function(req, res) {
  // Create a new instance of the Beer model
  var beer = new Beer();
  console.log('1.controller beer postBeers : ', req.body, req.user)
  // Set the beer properties that came from the POST data
  beer.name = req.body.name;
  beer.type = req.body.type;
  beer.quantity = req.body.quantity;
  beer.userId = req.user._id;

  // Save the beer and check for errors
  beer.save(function(err) {
    console.log('1.controller beer save : ', beer)
    if (err)
      return res.send(err);

    res.json({ message: 'Beer added to the locker!', data: beer });
  });
};

// Create endpoint /api/beers for GET
exports.getBeers = function(req, res) {
  // Use the Beer model to find all beer
  Beer.find({ userId: req.user._id }, function(err, beers) {
    console.log('1.controller beer getBeers : ', beers)
    if (err)
      return res.send(err);

    res.json(beers);
  });
};

// Create endpoint /api/beers/:beer_id for GET
exports.getBeer = function(req, res) {
  // Use the Beer model to find a specific beer
  Beer.find({ userId: req.user._id, _id: req.params.beer_id }, function(err, beer) {
    console.log('1.controller beer find : ', beer)
    if (err)
      return res.send(err);

    res.json(beer);
  });
};

// Create endpoint /api/beers/:beer_id for PUT
exports.putBeer = function(req, res) {
  // Use the Beer model to find a specific beer
  const query = { userId: req.user._id, _id: req.params.beer_id }
  const value = { quantity: req.body.quantity }
  Beer.update(query, value, function(err, num, raw) {
    console.log('1.controller beer putBeer : ', query, value)
    if (err)
      return res.send(err);

    res.json({ message: num + ' updated' });
  });
};

// Create endpoint /api/beers/:beer_id for DELETE
exports.deleteBeer = function(req, res) {
  // Use the Beer model to find a specific beer and remove it
  const query = { userId: req.user._id, _id: req.params.beer_id }
  Beer.remove(query, function(err) {
    console.log('1.controller beer deleteBeer : ', query)
    if (err)
      return res.send(err);

    res.json({ message: 'Beer removed from the locker!' });
  });
};