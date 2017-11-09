"use strict";

var express = require('express');
var firebase = require("firebase-admin");

var serviceAccount = require('path/to/serviceAccountKey.json');

firebase.initializeApp({
  credential: firebase.credential.cert(serviceAccount),
  databaseURL: 'https://<PROJECT_ID>.firebaseio.com'
});

// AC commands. Get information about ac status
var locationRef = firebase.database().ref('ac/');
locationRef.on('child_changed', function (data) {
    var ac = data.key;
    var status = data.val();
    console.log(ac + ": " + status);
});

var getDate = function () {
    var date = new Date();

    var year = date.getFullYear();

    var month = date.getMonth() + 1;
    month = (month < 10 ? "0" : "") + month;

    var day = date.getDate();
    day = (day < 10 ? "0" : "") + day;

    var hour = date.getHours();
    hour = (hour < 10 ? "0" : "") + hour;

    var min  = date.getMinutes();
    min = (min < 10 ? "0" : "") + min;

    var fullDate = day + "-" + month + "-" + year;
    var fullTime = hour + "h" + min;

    return {
        "day" : fullDate,
        "time" : fullTime
    }
}

// api
var app = express();

app.post('/sensor/api/:temperature', function (req, res) {
    var date = getDate();

    firebase.database().ref('/sensor/' + date.day).update({
        [date.time]: req.params.temperature
    });
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});