/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a estrutura HTML da página para o projeto de comunicação WiFi.
 * Data: 23/01/2025
 */

#ifndef HTML_H
#define HTML_H

// Função que retorna String que contem a estrutura HTML da página (incluindo CSS e JavaScript internos)
String getPage(){
    String page = "<!DOCTYPE html>";
    page += "<html lan=\"en-EN\">";
    page += "<head>";
    page += "<meta charset=\"UTF-8\">";
    page += "<meta http-equiv='refresh'/>";
    page += "<style media='screen' type='text/css'>";
    page += "html{display:inline-block; margin:10px;}";
    page += "body{background-image: linear-gradient(45deg, rgb(235, 247, 245), rgb(230, 241, 243));}";
    page += "h1 {text-align: center;font-size: 48px;font-weight: 700;font-family: 'Roboto', sans-serif;color: #2c3e50;margin-top: 20px;margin-bottom: 20px;text-transform: uppercase;letter-spacing: 2px}";
    page += "h2 {font-size: 35px;font-family: 'Verdana', sans-serif;color: #555;margin-top: 15px;margin-bottom: 15px;text-align: left}";
    page += ".Interactive{font-size: 40px;background-image: linear-gradient(45deg, rgb(242, 248, 230), rgb(212, 226, 245));display: flex;height: auto; flex-flow: column wrap;justify-content: center;align-items: center;text-align: center;margin: 1% 0% 1% 0%; box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);padding: 50px 0px 50px 0px;}";
    page += ".Interactive input{width: 800px; height: 90px; font-size: 40px; text-align: center}";
    page += ".Interactive h3{font-size: 30px;justify-content: left;}";
    page += ".ledButton {font-size: 40px;width: 300px;height: 100px;margin-top: 10px;border-radius: 50px}";
    page += ".ledButton:hover{background-color: black;color: white;}";
    page += ".submitButton{font-size: 20px;width: 150px;height: 50px;margin-top: 10px;border-radius: 50px}";
    page += ".submitButton:hover{background-color: black;color: white;}";
    page += "#received {background-color: white;width: 800px; text-align: center;height: 90px;border: 1px solid rgb(33, 33, 37); text-align: center;}";
    page += ".Evironment{background-image:linear-gradient(45deg, rgb(242, 248, 230), rgb(212, 226, 245));box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);padding: 50px 0px 50px 0px;display: flex;flex-flow: row nowrap;justify-content: center;padding: 5px}";
    page += ".Evironment .Interactive{background-image: linear-gradient(45deg, white, rgb(234, 240, 248)); margin: 20px 40px 20px 40px; padding: 2% 5% 2% ; width: 30%}";
    page += ".Evironment .Interactive h3{font-size: 65%;}";
    page += ".Evironment .Interactive:hover{opacity: 70%;}";
    page += "@media screen and (max-width: 1000px){";
    page += "#received {width: 400px;}";
    page += ".Interactive input{width: 400px;}";
    page += "}";
    page += "</style>";
    page += "<script>";
    page += "function updateReceived(){";
    page += "let id = document.getElementById('received');";
    page += "var xhr = new XMLHttpRequest();";
    page += "xhr.open('GET', '/received', true);";
    page += "xhr.onreadystatechange = function() {";
    page += "if (xhr.readyState == 4 && xhr.status == 200) {";
    page += "id.innerText = xhr.responseText";
    page += "}";
    page += "};";
    page += "xhr.send();";
    page += "}";
    page += "function updateTemperature(){";
    page += "let id = document.getElementById('temperature');";
    page += "var xhr = new XMLHttpRequest();";
    page += "xhr.open('GET', '/temp', true);";
    page += "xhr.onreadystatechange = function() {";
    page += "if (xhr.readyState == 4 && xhr.status == 200) {";
    page += "id.innerText = xhr.responseText + \" \u00B0 C\"";
    page += "}";
    page += "};";
    page += "xhr.send();";
    page += "}";
    page += "function updateHumidity(){";
    page += "let id = document.getElementById('humidity');";
    page += "var xhr = new XMLHttpRequest();";
    page += "xhr.open('GET', '/hum', true);";
    page += "xhr.onreadystatechange = function() {";
    page += "if (xhr.readyState == 4 && xhr.status == 200) {";
    page += "id.innerText = xhr.responseText + \"%\"";
    page += "}";
    page += "};";
    page += "xhr.send();";
    page += "}";
    page += "function sendLed(event){";
    page += "event.preventDefault();";
    page += "var xhr = new XMLHttpRequest();";
    page += "xhr.open('POST', '/', true);";
    page += "xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');";
    page += "xhr.onreadystatechange = function(){";
    page += "if(xhr.readyState == 4 && xhr.status == 200){";
    page += "console.log('Log submit successfully');";
    page += "}";
    page += "};";
    page += "let ledForm = new FormData(document.getElementById('ledForm'));";
    page += "xhr.send(new URLSearchParams(ledForm).toString());";
    page += "}";
    page += "function sendMsg(event){";
    page += "event.preventDefault();";
    page += "var xhr = new XMLHttpRequest();";
    page += "xhr.open('POST', '/', true);";
    page += "xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');";
    page += "xhr.onreadystatechange = function(){";
    page += "if(xhr.readyState == 4 && xhr.status == 200){";
    page += "console.log('Log submit successfully');";
    page += "}";
    page += "};";
    page += "let msgForm = new FormData(document.getElementById('msgForm'));";
    page += "xhr.send(new URLSearchParams(msgForm).toString());";
    page += "document.getElementById('msgForm').querySelector('input[type=\"text\"]').value = '';";
    page += "document.querySelector('.submitButton').disabled = true;";
    page += "document.querySelector('.submitButton').disabled = false;";
    page += "}";
    page += "setInterval(updateReceived, 1000);";
    page += "setInterval(updateTemperature, 500);";
    page += "setInterval(updateHumidity, 500);";
    page += "</script>";
    page += "</head>";
    page += "<body>";
    page += "<h1> IOT Page </h1>";
    page += "<h2>Light control</h2>";
    page += "<div class=\"Interactive\"><form action=\"/\" method=\"post\">";
    page += "<p><button class=\"ledButton\" type=\"submit\" name=\"LED_ON\" value=\"on\">ON</button></p>";
    page += "<p><button class=\"ledButton\" type=\"submit\" name=\"LED_OFF\" value=\"off\">OFF</button></p></form></div>";
    page += "<br><br>";
    page += "<h2>Evironment</h2>";
    page += "<div class=\"Evironment\">";
    page += "<div class=\"Interactive\"><h3>Temperature</h3><p id=\"temperature\"></p></div>";
    page += "<div class=\"Interactive\"><h3>Humidity</h3><p id=\"humidity\"></p></div>";
    page += "</div>";
    page += "<br><br>";
    page += "<h2>Messages for MCU</h2>";
    page += "<div class=\"Interactive\"><form id=\"msgForm\" onsubmit=\"sendMsg(event)\"><h3>Message</h3><p><input type=\"text\" id=\"client\" name=\"clientMsg\" ></p><p><button class=\"submitButton\" type=\"submit\">Send</button></p></form></div>";
    page += "<br><br>";
    page += "<h2>Messages from MCU</h2>";
    page += "<div class=\"Interactive\"><h3>Received</h3><p id=\"received\"></p></div>";
    page += "</body>";
    page += "</html>";
    return page;
}

#endif