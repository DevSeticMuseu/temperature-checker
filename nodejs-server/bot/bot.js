"use strict";

const TeleBot = require('telebot');
const token = require('./token');

const bot = new TeleBot(token);

const initFire = require('../components/db/initFire');
const time = require('../components/time/time');

const date = time.getDate();

bot.on('/status', (msg) => {
    if (msg.from.id === 250238939){
        // return bot.sendMessage(msg.from.id, `Hello, ${msg.from.first_name}!, ${msg.from.id}`);

        var ref = initFire.firebase.database().ref(`sensor/12-11-2017`);
        ref.orderByChild('time').limitToLast(1).once('value').then(function(snapshot){
            if(snapshot){
                console.log(snapshot.key);
                console.log('TEmperature: '+ snapshot.val());
            }
        });

        initFire.firebase.database().ref('airConditioner/ac1/status').once('value').then(function(snapshot){
            if(snapshot){
                console.log('Ar condicionado 1: '+ snapshot.val());
            }
        });

        initFire.firebase.database().ref('airConditioner/ac2/status').once('value').then(function(snapshot){
            if(snapshot){
                console.log('Ar condicionado 2: '+ snapshot.val());
            }
        });
    }
});

bot.on('/hello', (msg) => {
    console.log('hello');
});

bot.start();