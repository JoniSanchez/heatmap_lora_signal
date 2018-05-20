var mqtt = require('./')
var client = mqtt.connect('mqtt://localhost')

client.subscribe('#')

client.on('message', function (topic, message) {
  console.log(message.toString())
})

client.end()
