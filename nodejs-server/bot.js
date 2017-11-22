"use strict";

const TeleBot = require('telebot');
const bot = new TeleBot('tokenbot');

const initFire = require('./init');
const time = require('./time');

bot.on('/status', (msg) => {
    if (msg.from.id === 250238939){
        // return bot.sendMessage(msg.from.id, `Hello, ${msg.from.first_name}!, ${msg.from.id}`);

        initFire.firebase.database().ref('airConditioner/ac1/status').once('value').then(function(snapshot){
            if(snapshot){
                console.log('Ar condicionado 1: '+ snapshot.val());
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

bot.start();