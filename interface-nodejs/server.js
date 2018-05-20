'use strict';

const express = require('express');
// Constants
const PORT = 8082;
const HOST = '0.0.0.0';

// App
const app = express();
app.use(express.static('public'));
app.get('/', (req, res) => {
  res.sendFile( __dirname + "/" + "public/index.htm" );
});

app.listen(PORT, HOST);
console.log(`Running on http://${HOST}:${PORT}`);