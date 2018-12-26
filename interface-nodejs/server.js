var express = require("express"),
    app = express(),
    bodyParser  = require("body-parser"),
    methodOverride = require("method-override");
//var expressMongoDb = require('express-mongo-db');
var expressValidator = require('express-validator');
var flash = require('express-flash');

// Middlewares

//app.use(expressMongoDb('mongodb://localhost:27017/lora'));
app.set('view engine', 'ejs')
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(methodOverride());
app.use(expressValidator());

app.use(methodOverride(function (req, res) {
  if (req.body && typeof req.body === 'object' && '_method' in req.body) {
    // look in urlencoded POST bodies and delete it
    var method = req.body._method
    delete req.body._method
    return method
  }
}))

// Import Models and controllers
var router = express.Router();
var data = require('./routes/data')
var principal = require('./routes/principal')

// API routes
app.use('/dashboard', data)
app.use('/', principal)


// Start server
app.listen(8082, function() {
  console.log("Node server running on http://localhost:8082");
});