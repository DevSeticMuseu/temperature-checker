"use strict";

const TeleBot = require('telebot');
const token = require('./token');

const bot = new TeleBot(token);

const initFire = require('../components/db/initFire');
const time = require('../components/time/time');

const date = time.getDate();

bot.on('/status', function (msg) {
    if (msg.from.id === 250238939) {

        var ref = initFire.firebase.database().ref('lm35/' + date.day);
        ref.limitToLast(1).once('value', function (snapshot) {
            snapshot.forEach(function (childSnapshot) {
                return bot.sendMessage(msg.from.id, `Última temperatura medida: ${childSnapshot.val().temperature}º`);
            });
        });

        initFire.firebase.database().ref('airConditioner/').once('value', function (snapshot) {
            snapshot.forEach(function (childSnapshot) {
                var on = (childSnapshot.val().status) ? 'Ligado' : 'Desligado';
                bot.sendMessage(msg.from.id, `${childSnapshot.val().number}: ${on}`);
            });
        });

    }
});

bot.on('/last7', function (msg) {
    if (msg.from.id === 250238939) {
        var message = 'As últimas 7 temperaturas medidas foram: ';

        var ref = initFire.firebase.database().ref('lm35/' + date.day);
        var refPromise = ref.limitToLast(2).once('value', function (snapshot) {
            snapshot.forEach(function (childSnapshot) {
                message += childSnapshot.val().temperature + 'º ';
            });
        });

        refPromise.then(function (val) {
            bot.sendMessage(msg.from.id, message);
        });
    }
});

bot.on('/temperatura', function (msg) {
    if (msg.from.id === 250238939) {
        var ref = initFire.firebase.database().ref('lm35/' + date.day);
        ref.limitToLast(1).once('value', function (snapshot) {
            snapshot.forEach(function (childSnapshot) {
                return bot.sendMessage(msg.from.id, `Última temperatura medida: ${childSnapshot.val().temperature}º`);
            });
        });
    }
});


bot.on(/^\/ar (.+)$/, (msg, props) => {
    if (msg.from.id === 250238939) {
        let approved = false;
        const input = props.match[1];

        const ackInput = [
            '1 ligado',
            '1 desligado',
            '2 ligado',
            '2 desligado'
        ];

        ackInput.map(function (ack) {
            if (ack === input) approved = true;
        });

        if (approved) {
            const inputArray = input.split(' ');
            const ligado = (inputArray[1] === 'ligado') ? true : false;

            const promisa = initFire.firebase.database()
                .ref('airConditioner/' + inputArray[0])
                .update({ status: ligado });

            promisa.then(bot.sendMessage(msg.from.id, `O ar condicionado ${inputArray[0]} foi ${inputArray[1]}`));
        } else {
            bot.sendMessage(msg.from.id, 'Comando não reconhecido');
        }
    }
});

bot.start();