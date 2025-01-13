#ifndef HTML_H
#define HTML_H

String getPage(String output){
    String html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    html += "<title>WiFi Communication</title>";
    html += "</head>";
    html += "<body>";
    html += "<h1 style=\"font-size: 40px;\"> Pagina IOT </h1>";
    html += "<h2>Acendimento de leds</h2>";
    html += "<form action=\"/\" method=\"post\">";
    html += "<p><button style=\"font-size: 40px; width: 100px\" type=\"submit\" name=\"LED_ON\" value=\"on\">ON</button></p>";
    html += "<p><button style=\"font-size: 40px; width: 100px\" type=\"submit\" name=\"LED_OFF\" value=\"off\">OFF</button></p>";
    html += "</form>";
    html += "<br><br>";
    html += "<h2>Comunicacao</h2>";
    html += "<form action=\"/\" method=\"post\">";
    html += "<label for=\"cliente\">Mensagem: </label>";
    html += "<input type=\"text\" id=\"cliente\" name=\"clientMsg\" maxlength=\"12\">";
    html += "<button type=\"submit\">Enviar</button>";
    html += "</form>";
    html += "<br>";
    html += "<div>";
    html += "<text id=\"Estacao\">Recebido: " + output + "</text>";
    html += "</div>";
    html += "</body>";
    html += "</html>";
    return html;
}

#endif