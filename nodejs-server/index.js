"use strict";

var express = require('express');
var admin = require("firebase-admin");

var serviceAccount = require('path/to/serviceAccountKey.json');

firebase.initializeApp({
  credential: firebase.credential.cert(serviceAccount),
  databaseURL: 'https://<PROJECT_ID>.firebaseio.com'
});

// AC commands. Get information about ac status
var locationRef = admin.database().ref('ac/');
locationRef.on('child_changed', function (data) {
    var ac = data.key;
    var status = data.val();
    console.log(ac + ": " + status);
});

var getTime = function () {
    var date = new Date();
}

// api
var app = express();

app.post('/sensor/api/:temperature', function (req, res) {
    //Get current time to alocate in firebase
    getTime();

    // var temperature = req.params.temperature;
    admin.database().ref('/sensor/').update({
        temperature: req.params.temperature
    });
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});