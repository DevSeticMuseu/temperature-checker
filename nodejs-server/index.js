var express = require('express');
var admin = require("firebase-admin");

var serviceAccount = require('path/to/serviceAccountKey.json');

admin.initializeApp({
    credential: firebase.credential.cert(serviceAccount),
    databaseURL: 'https://<PROJECT_ID>.firebaseio.com'
});

var app = express();

app.get('/:name', function (req, res) {
    console.log('USER ' +req.params.name);
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});

