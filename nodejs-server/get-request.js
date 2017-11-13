"use strict";

const http = require('http');

const init = require('./init');

// AC commands. Get information about ac status
const locationRef = init.firebase.database().ref('ac/');

locationRef.on('child_changed', function (data) {
    const ac = data.key;
    const status = data.val();

    console.log(`${ac}=${status}`)
    makeRequest(ac, status);
});

const makeRequest = function(ac, status){
    const url = `http://10.42.0.17/temperature-manager/api/${ac}?status=${status}`;

    http.get(url, function (res) {
        res.setEncoding('utf8');
        res.on('data', function(chunk){
            console.log('Body: ' + chunk);
        });
    });
};