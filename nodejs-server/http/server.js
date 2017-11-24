"use strict";

const http = require('http');
const url = require('url');

const initFire = require('../components/db/initFire');
const time = require('../components/time/time');

http.createServer(function (req, res) {
    const parsedUrl = url.parse(req.url, true); // true to get query as object

    const pathname = parsedUrl.pathname;
    const query = parsedUrl.query;

    if (pathname === '/temperature-manager/api/lm') {
        const date = time.getDate();

        initFire.firebase.database().ref('lm35/' + date.day + '/' + date.time).update({
            "temperature": query.temperature,
            "time": date.time
        });
    }

    res.end();
}).listen(3000);