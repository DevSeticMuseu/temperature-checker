"use strict";

const http = require('http');
const url = require('url');

const init = require('./init');

http.createServer(function (req, res) {
    const parsedUrl = url.parse(req.url, true); // true to get query as object

    const pathname = parsedUrl.pathname;
    const query = parsedUrl.query;

    if (pathname === '/temperature-manager/api/lm') {
        const date = getDate();

        init.firebase.database().ref('/sensor/' + date.day).update({
            [date.time]: query.temperature
        });
    }

    res.end();
}).listen(3000);