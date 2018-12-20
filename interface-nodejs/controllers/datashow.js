//File: controllers/datashow.js
var mongoose = require('mongoose');
var datas  = mongoose.model('MQTTDB');

//GET - Return all datashow in the DB
exports.findAllData = function(req, res) {
	datas.find(function(err, lora) {
    if(err) res.send(500, err.message);

    console.log('GET /datashow')
		res.status(200).jsonp(lora);
	});
};