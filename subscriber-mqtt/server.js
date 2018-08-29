var mqtt = require('./mqtt.js')
var client = mqtt.connect('http://broker');
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
	  var messageStr = message.toString();
	  var strLeng = messageStr.lenght;
	  var count = 0;
	  if (messageStr.indexOf('{"rxpk') + 1 ){
		  while (messageStr.charAt(count) != '{'){
	          count = count + 1;
		  }
		  var responseStr = messageStr.substring(count, strLeng);	
		  responseJSON = JSON.parse(responseStr);
		  var rssi = responseJSON.rxpk[0].rssi;
		  parseInt(rssi, 10);
		  rssi = ((rssi + 100) / 2);
		  var dataPayload = responseJSON.rxpk[0].data;	
		  var bufferData = Buffer.from(dataPayload, 'base64');
		  var bufferData = bufferData + " ";
		  var bufferDataArray = bufferData.split(";");
		  for(var i = 0; i < bufferDataArray.length - 1; i++) {
			  bufferDataArray[i] = +bufferDataArray[i];
		  }
		  if (bufferDataArray[2] != null){
			  db.collection('position').insert({latitude:bufferDataArray[0], longitude:bufferDataArray[1], intensity:rssi});
		  }
		  db.close();
	  }
  });
});