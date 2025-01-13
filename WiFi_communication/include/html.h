#ifndef HTML_H
#define HTML_H

String getPage(){
    #include <Arduino.h>
    String html = "<!DOCTYPE html>";
    html += "<html lang=en-EN>";
    html += "<head>";
    html += "<meta http-equiv='refresh' content='60'/>";
    html += "<style media='screen' type='text/css'>";
    html += "html{display:inline-block; margin:10px;}";
    html += "body{background-image: linear-gradient(45deg, rgb(248, 248, 248), rgb(209, 204, 204));}";
    html += "h1{text-align: center;font-size: 40px;}";
    html += "h2{margin-bottom: 0px;}";
    html += ".Interactive{font-size: 40px;background-image: linear-gradient(45deg, white, rgb(234, 240, 248));display: flex;height: auto; flex-flow: column wrap;justify-content: center;align-items: center;text-align: center;margin: 1% 0% 1% 0%; box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);padding: 50px 0px 50px 0px;}";
    html += ".Interactive input{font-size: 40px;width: 90%;}";
    html += ".Interactive text{background-color: white;width: 90%;height: 90px;border: 1px solid rgb(33, 33, 37);}";
    html += ".Interactive h3{font-size: 30px;justify-content: left;}";
    html += ".ledButton {font-size: 40px;width: 300px;height: 100px;margin-top: 10px;border-radius: 50px}";
    html += ".ledButton:hover{background-color: black;color: white;}";
    html += ".submitButton{font-size: 20px;width: 150px;height: 50px;margin-top: 10px;border-radius: 50px}";
    html += ".submitButton:hover{background-color: black;color: white;}";
    html += "#received {background-color: white;width: 90%; text-align: center;height: 90px;border: 1px solid rgb(33, 33, 37); text-align: center;}";
    html += "</style>";
    html += "<script>";
    html += "function updateReceived(){";
    html += "let id = document.getElementById('received');";
    html += "var xhr = new XMLHttpRequest();";
    html += "xhr.open('GET', '/update', true);";
    html += "xhr.onreadystatechange = function() {";
    html += "if (xhr.readyState == 4 && xhr.status == 200) {";
    html += "id.innerText = xhr.responseText;";
    html += "}";
    html += "};";
    html += "xhr.send();";
    html += "}";
    html += "setInterval(updateReceived, 1000);";
    html += "</script>";
    html += "</head>";
    html += "<body>";
    html += "<h1 style=\"font-size: 40px;\"> IOT Page </h1>";
    html += "<h2>Activity leds</h2>";
    html += "<div class=\"Interactive\"><form action=\"/\" method=\"post\">";
    html += "<p><button class=\"ledButton\" type=\"submit\" name=\"LED_ON\" value=\"on\">ON</button></p>";
    html += "<p><button class=\"ledButton\" type=\"submit\" name=\"LED_OFF\" value=\"off\">OFF</button></p></form></div>";
    html += "<br><br>";
    html += "<h2>Messages for MCU</h2>";
    html += "<div class=\"Interactive\"><form action=\"/\" method=\"post\"><h3>Mensagem</h3><p><input type=\"text\" id=\"client\" name=\"clientMsg\" ></p><p><button class=\"submitButton\" type=\"submit\">Enviar</button></p></form></div>";
    html += "<br><br>";
    html += "<h2>Messages from MCU</h2>";
    html += "<div class=\"Interactive\"><h3>Recebido</h3><p id=\"received\"></p></div>";
    html += "</body>";
    html += "</html>";
    return html;
}

#endif