"use strict";

const http = require('http');

const initFire = require('../components/db/initFire');

// AC commands. Get information about ac status
const ac1Ref = initFire.firebase.database().ref('airConditioner/1');
const ac2Ref = initFire.firebase.database().ref('airConditioner/2');

ac1Ref.on('child_changed', function (data) {
    const ac = data.key;
    const status = data.val().status;

    console.log(`${ac}=${status}`)
    makeRequest(ac, status);
});

ac2Ref.on('child_changed', function (data) {
    const ac = data.key;
    const status = data.val().status;

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