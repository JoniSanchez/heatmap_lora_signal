var mqtt = require('./mqtt.js')
var client = mqtt.connect('http://localhost');
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://mongo:27017/lora";

client.on('connect', function () {
  client.subscribe('#');
})

client.on('message', function (topic, message) {
  MongoClient.connect(url, function(err, db) {
  if(!err) {
    console.log("We are connected");
  }
  var data = { topic: topic.toString(), value: message.toString() };
  db.collection('documents').insertOne(data, function(err, res) {
    if (err) throw err;
    console.log("Document inserted");
  });
  db.close();
  console.log(message.toString());
  });
});

console.log('Client started...');