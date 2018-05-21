var mqtt = require('./')
var client = mqtt.createClient(1883, 'localhost');
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://localhost:27017/lora";

// Connect to the db
MongoClient.connect(url, function(err, db) {
  if(!err) {
    console.log("We are connected");
  }
});

client.subscribe('#');

client.on('message', function (topic, message) {
  var data = { topic: topic.toString(), value: message.toString() };
  db.collection('documents').insertOne(data, function(err, res) {
    if (err) throw err;
    console.log("Document inserted");
  });
  console.log(message.toString());
});

console.log('Client started...');