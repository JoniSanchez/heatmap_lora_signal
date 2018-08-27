var express = require('express')
var app = express();
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://mongo:27017/lora";
const resultQuery = "test";
module.exports = app;

app.get('/', function(req, res, next) {
  MongoClient.connect(url, function(err, db) {
  if(!err) {
    console.log("We are connected");
  }
  db.position.find().toArray(function(err, result) {
  	  if (err) throw err; 
     resultQuery = result;
  });
  db.close();
  });
  res.render('data/list', {
      title: 'Data List',
      data: resultQuery
  });
});