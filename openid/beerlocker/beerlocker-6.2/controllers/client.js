// Load required packages
var Client = require('../models/client');
require('debug')('controller:client');
// Create endpoint /api/client for POST
exports.postClients = function(req, res) {
  // Create a new instance of the Client model
  var client = new Client();

  // Set the client properties that came from the POST data
  client.name = req.body.name;
  client.id = req.body.id;
  client.secret = req.body.secret;
  client.userId = req.user._id;

  // Save the client and check for errors
  client.save(function(err) {
    console.log('1.controller client postClients : ', client)
    if (err)
      return res.send(err);

    res.json({ message: 'Client added to the locker!', data: client });
  });
};

// Create endpoint /api/clients for GET
exports.getClients = function(req, res) {
  // Use the Client model to find all clients
  const query = { userId: req.user._id }
  Client.find(query, function(err, clients) {
    console.log('1.controller client getClients : ', query, clients)
    if (err)
      return res.send(err);

    res.json(clients);
  });
};