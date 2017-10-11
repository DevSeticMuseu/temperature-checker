<?php
/**
 * This example shows making an SMTP connection without using authentication.
 */

//SMTP needs accurate times, and the PHP time zone MUST be set
//This should be done in your php.ini, but this is how to do it if you don't have access to that
date_default_timezone_set('Etc/UTC');


//Call Autoloader
require_once './classes/PHPMailerAutoload.php';


//Create a new PHPMailer instance
$mail = new PHPMailer;
//Use UTF-8 characters
$mail->CharSet = 'UTF-8';
//Tell PHPMailer to use SMTP
$mail->isSMTP();
//Enable SMTP debugging
// 0 = off (for production use)
// 1 = client messages
// 2 = client and server messages
$mail->SMTPDebug = 0;
//Ask for HTML-friendly debug output
$mail->Debugoutput = 'html';
//Set the hostname of the mail server
$mail->Host = "smtp.museu-goeldi.br";
//Set the SMTP port number - likely to be 25, 465 or 587
$mail->Port = 25;
//Whether to use SMTP authentication
$mail->SMTPAuth = false;
//Set who the message is to be sent from
$mail->setFrom('devsetic@museu-goeldi.br', 'Datacenter');
//Set who the message is to be sent to
$mail->addAddress('alves.jnts@gmail.com', 'Jonatas Alves');
$mail->addAddress('raniery@museu-goeldi.br', 'Raniery Pontes');
$mail->addAddress('thiagosylas@museu-goeldi.br', 'Thiago Sylas');

$mail->IsHTML(true);


//Set the subject line
$mail->Subject = 'A temperatura no datacenter diminuiu';
//Read an HTML message body from an external file, convert referenced images to embedded,
//convert HTML into a basic plain-text alternative body
$mail->Body='Atualmente o sensor está medindo uma temperatura constante de '.$_GET["temperatura"];

//send the message, check for errors
if (!$mail->send()) {
    echo "Mailer Error: " . $mail->ErrorInfo;
} else {
    echo "Message sent!";
}
