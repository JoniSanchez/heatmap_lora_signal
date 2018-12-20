var mongoose = require('mongoose'),
	Schema = mongoose.Schema;
	
	var mqttdbSchema = new Schema({
	  topic:    { type: String },
	  value:     { type: String }
	});
	
module.exports = mongoose.model('MQTTDB', mqttdbSchema);