var express = require("express"),
    app = express(),
    bodyParser  = require("body-parser"),
    methodOverride = require("method-override"),
    mongoose = require('mongoose');

// Connection to DB
mongoose.connect('mongodb://localhost/lora', function(err, res) {
  if(err) throw err;
  console.log('Connected to Database');
});

// Middlewares
  
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(methodOverride());


// Import Models and controllers
var models     = require('./models/datashow')(app, mongoose);
var DataShowCtrl = require('./controllers/datashow');
var router = express.Router();

//ROUTE
router.get('/', function(req, res) {
   res.send("Hello World!");
});
app.use(router);

// API routes
var datashows = express.Router();

datashows.route('/datashow').get(DataShowCtrl.findAllData);

app.use('/api', datashows);

// Start server
app.listen(8082, function() {
  console.log("Node server running on http://localhost:8082");
});