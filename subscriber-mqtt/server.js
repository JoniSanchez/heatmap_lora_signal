var lora_packet = require('lora-packet');
var mqtt = require('./mqtt.js')
var client = mqtt.connect('http://broker');
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://mongo:27017/lora";

client.on('connect', function () {
  client.subscribe('gateway/c0ee40ffff294c1f/rx');
})

client.on('message', function (topic, message) {
  MongoClient.connect(url, function(err, db) {
	  if(!err) {
		  console.log("We are connected");
	  }
	  var messageStr = message.toString();
	  var responseJSON = JSON.parse(messageStr);
	  var rssi = responseJSON.rxInfo.rssi;
	  parseInt(rssi, 10);
	  rssi = ((rssi + 100) / 2);
	  if (rssi < 0){
		  rssi = 1;
	  }
	  var dataPayload = responseJSON.phyPayload;
	  var packet = lora_packet.fromWire(new Buffer(dataPayload, 'base64'));
	  var NwkSKey = new Buffer('01020304050607080910111213141516', 'hex');
	  var AppSKey = new Buffer('000102030405060708090A0B0C0D0E0F', 'hex');
	  var resultPacket = lora_packet.decrypt(packet, AppSKey, NwkSKey).toString()
	  var bufferDataArray = resultPacket.split(";");
	  for(var i = 0; i < bufferDataArray.length - 1; i++) {
		  bufferDataArray[i] = +bufferDataArray[i];
	  }
	  if (bufferDataArray[0] != null && bufferDataArray[1] != null && bufferDataArray[2] != null
			 && bufferDataArray[0].toString().trim() !== "NaN" && bufferDataArray[1].toString().trim() !== "NaN"){
		  db.collection('position').insert({latitude:bufferDataArray[0], longitude:bufferDataArray[1], intensity:rssi});
	  }
	  db.close();
  });
});
