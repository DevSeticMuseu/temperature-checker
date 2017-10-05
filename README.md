# Medidor de temperatura

Projeto medidor de temperatura. Utilizando a placa NodeMCU ESP8266 com o componente LM35, este projeto visa receber e tratar informações de temperatura em um ambiente.

## Requisitos

* Arduino IDE
* Servidores PHP e SMTP

## Instalação

Baixe e instale a IDE do arduino. (https://www.arduino.cc/en/main/software);

Instale a biblioteca do ESP8266:
    * File > Preferences
    * Em Additional Boards Manager URLs cole "https://www.arduino.cc/en/main/software";
    * Tools > Boards > Boards Manager, encontre e baixe a biblioteca ESP8266;
    * Reinicie a IDE e troque a placa usada em Tools > Boards para NodeMCU EP8266.

## Componentes

* [Módulo Wifi ESP8266] - Placa utilizada.
* [LM35]- Sensor de temperatura.
* [PHPMailer] (https://github.com/PHPMailer/PHPMailer) - Biblioteca de email php.


## Autores

* **Equipe de desenvolvimento SETIC** - [DevSeticMuseu] (https://github.com/devseticmuseu)


## Acknowledgments

* PHPMailer - [https://github.com/PHPMailer/]
* Wemos - [http://educ8s.tv/]

