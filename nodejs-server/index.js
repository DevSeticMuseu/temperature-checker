var express = require('express');
var admin = require("firebase-admin");

var serviceAccount = require('path/to/serviceAccountKey.json');

firebase.initializeApp({
  credential: firebase.credential.cert(serviceAccount),
  databaseURL: 'https://<PROJECT_ID>.firebaseio.com'
});

// AC commands
var locationRef = admin.database().ref('ac/');
locationRef.on('child_changed', function (data) {
    var status = data.key;
    var on = data.val();
    console.log(status + ": " + on);
});

// api
var app = express();

app.get('/:temperature', function (req, res) {
    // var temperature = req.params.temperature;
    admin.database().ref('/').update({
        temperature: req.params.temperature
    });
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});