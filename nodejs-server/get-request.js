"use strict";

const http = require('http');

const init = require('./init');

// AC commands. Get information about ac status
const locationRef = init.firebase.database().ref('ac/');

locationRef.on('child_changed', function (data) {
    const ac = data.key;
    const status = data.val();

    makeRequest(ac, status);
});

const makeRequest = function(ac, status){
    const url = `http://192.168.0.17/temp/api/${ac}/${status}`
    
    http.get(url, function (res) {
        res.setEncoding('utf8');
        res.on('data', function(chunk){
            console.log('Body: ' + chunk);
        });
    });
};