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

const getDate = function () {
    var date = new Date();

    var year = date.getFullYear();

    var month = date.getMonth() + 1;
    month = (month < 10 ? "0" : "") + month;

    var day = date.getDate();
    day = (day < 10 ? "0" : "") + day;

    var hour = date.getHours();
    hour = (hour < 10 ? "0" : "") + hour;

    var min = date.getMinutes();
    min = (min < 10 ? "0" : "") + min;

    var fullDate = day + "-" + month + "-" + year;
    var fullTime = hour + "h" + min;

    return {
        "day": fullDate,
        "time": fullTime
    }
}