/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a estrutura HTML da página para o projeto de comunicação WiFi.
 * Data: 23/01/2025
 */

#ifndef HTML_H
#define HTML_H

#include <Arduino.h>

// Função que retorna String que contem a estrutura HTML da página (incluindo CSS e JavaScript internos)
String getPage(){
    String page = String(R"(
        <!DOCTYPE html>
        <html lan="en-EN">
            <head>
                <meta charset="UTF-8" />
                <style media="screen" type="text/css">
                    html {
                    display: inline-block;
                    margin: 10px;
                    }
                    body {
                    background-image: linear-gradient(
                        45deg,
                        rgb(235, 247, 245),
                        rgb(230, 241, 243)
                    );
                    }
                    h1 {
                    text-align: center;
                    font-size: 48px;
                    font-weight: 700;
                    font-family: "Roboto", sans-serif;
                    color: #2c3e50;
                    margin-top: 20px;
                    margin-bottom: 20px;
                    text-transform: uppercase;
                    letter-spacing: 2px;
                    }
                    h2 {
                    font-size: 35px;
                    font-family: "Verdana", sans-serif;
                    color: #555;
                    margin-top: 15px;
                    margin-bottom: 15px;
                    text-align: left;
                    }
                    .Interactive {
                    font-size: 40px;
                    background-image: linear-gradient(
                        45deg,
                        rgb(232, 235, 228),
                        rgb(229, 235, 222),
                    );
                    display: flex;
                    height: auto;
                    flex-flow: column wrap;
                    justify-content: center;
                    align-items: center;
                    text-align: center;
                    margin: 1% 0% 1% 0%;
                    box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2),
                        0 6px 20px 0 rgba(0, 0, 0, 0.19);
                    padding: 50px 0px 50px 0px;
                    }
                    .Interactive input {
                    width: 800px;
                    height: 90px;
                    font-size: 40px;
                    text-align: center;
                    }
                    .Interactive h3 {
                    font-size: 30px;
                    justify-content: left;
                    }
                    .ledButton {
                    font-size: 40px;
                    width: 300px;
                    height: 100px;
                    margin-top: 10px;
                    border-radius: 50px;
                    }
                    .ledButton:hover {
                    background-color: black;
                    color: white;
                    }
                    .submitButton {
                    font-size: 20px;
                    width: 150px;
                    height: 50px;
                    margin-top: 10px;
                    border-radius: 50px;
                    }
                    .submitButton:hover {
                    background-color: black;
                    color: white;
                    }
                    #received {
                    background-color: white;
                    width: 800px;
                    text-align: center;
                    height: 90px;
                    border: 1px solid rgb(33, 33, 37);
                    text-align: center;
                    }
                    .Evironment {
                    background-image: linear-gradient(
                        45deg,
                        rgb(232, 235, 228),
                        rgb(229, 235, 222),
                    );
                    box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2),
                        0 6px 20px 0 rgba(0, 0, 0, 0.19);
                    padding: 50px 0px 50px 0px;
                    display: flex;
                    flex-flow: row nowrap;
                    justify-content: center;
                    padding: 5px;
                    }
                    .Evironment .Interactive {
                    background-image: linear-gradient(45deg, white, rgb(234, 240, 248));
                    margin: 20px 40px 20px 40px;
                    padding: 2% 5% 2%;
                    width: 30%;
                    }
                    .Evironment .Interactive h3 {
                    font-size: 65%;
                    }
                    .Evironment .Interactive:hover {
                    opacity: 70%;
                    }
                    @media screen and (max-width: 1000px) {
                    #received {
                        width: 400px;
                    }
                    .Interactive input {
                        width: 400px;
                    }
                    }
                </style>
                <script>
                    // Função que atualiza campo de dados recebidos do servidor
                    function updateReceived(){
                        let id = document.getElementById('received');       // recebe elemento com a id de recepção de dados
                        var xhr = new XMLHttpRequest();                     // variável de requisição
                        xhr.open('GET', '/received', true);                   // cria requisição para usar método GET e a URL \update
                        xhr.onreadystatechange = function() {               // cria função para ser chamada quando o estado de requisição mudar
                            
                            if (xhr.readyState == 4/*requisição completa*/ && xhr.status == 200/*requisição bem sucedida*/) {
                                id.innerText = xhr.responseText             // atualização do conteúdo do ID com a resposta da requisição
                            }
                        };
                        xhr.send();                                         // envia requisição
                    }
                    function updateTemperature(){
                        let id = document.getElementById('temperature');       // recebe elemento com a id de recepção de dados
                        var xhr = new XMLHttpRequest();                     // variável de requisição
                        xhr.open('GET', '/temp', true);                     // cria requisição para usar método GET e a URL \temp
                        xhr.onreadystatechange = function() {               // cria função para ser chamada quando o estado de requisição mudar
                            
                            if (xhr.readyState == 4/*requisição completa*/ && xhr.status == 200/*requisição bem sucedida*/) {
                                id.innerText = xhr.responseText + " °C"     // atualização do conteúdo do ID com a resposta da requisição
                            }
                        };
                        xhr.send();                                         // envia requisição
                    }
                    function updateHumidity(){
                        let id = document.getElementById('humidity');       // recebe elemento com a id de recepção de dados
                        var xhr = new XMLHttpRequest();                     // variável de requisição
                        xhr.open('GET', '/hum', true);                      // cria requisição para usar método GET e a URL \hum
                        xhr.onreadystatechange = function() {               // cria função para ser chamada quando o estado de requisição mudar
                            
                            if (xhr.readyState == 4/*requisição completa*/ && xhr.status == 200/*requisição bem sucedida*/) {
                                id.innerText = xhr.responseText + " %"      // atualização do conteúdo do ID com a resposta da requisição
                            }
                        };
                        xhr.send();                                         // envia requisição
                    }
                    function sendLed(event){
                        event.preventDefault();                             // previne o comportamento padrão do formulário
                        var xhr = new XMLHttpRequest();                     // variável de requisição
                        xhr.open('POST', '/', true);                        // cria requisição para usar método POST e a URL \update
                        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded'); // define o tipo de conteúdo da requisição
                        xhr.onreadystatechange = function(){                // cria função para ser chamada quando o estado de requisição mudar
                            if(xhr.readyState == 4 && xhr.status == 200){   // verifica se a requisição foi completada e bem sucedida
                                console.log('Log submit successfully');     // imprime no console que a requisição foi bem sucedida
                            }
                        };
                        let ledForm = new FormData(document.getElementById('ledForm')); // cria um formulário com os dados do formulário com a id ledForm
                        xhr.send(new URLSearchParams(ledForm).toString());              // envia a requisição com os dados do formulário
                    }
                    function sendMsg(event){
                        event.preventDefault();                             // previne o comportamento padrão do formulário
                        var xhr = new XMLHttpRequest();                     // variável de requisição
                        xhr.open('POST', '/', true);                        //  cria requisição para usar método POST e a URL \update
                        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');  // define o tipo de conteúdo da requisição
                        xhr.onreadystatechange = function(){                // cria função para ser chamada quando o estado de requisição mudar 
                            if(xhr.readyState == 4 && xhr.status == 200){   // verifica se a requisição foi completada e bem sucedida
                                console.log('Log submit successfully');     // imprime no console que a requisição foi bem sucedida
                                document.querySelector('.submitButton').disabled = true; // Desabilita o botão
                            }
                        };
                        let msgForm = new FormData(document.getElementById('msgForm')); // cria um formulário com os dados do formulário com a id msgForm
                        xhr.send(new URLSearchParams(msgForm).toString());              // envia a requisição com os dados do formulário
                        
                        document.getElementById('msgForm').querySelector('input[type="text"]').value = '';  // Limpa o campo de texto
                        document.querySelector('.submitButton').disabled = false;                           // Habilita o botão
                    }
                    
                    // Script realizado a cada 1 segundo 
                    setInterval(updateReceived, 1000);
                    setInterval(updateTemperature, 1000);
                    setInterval(updateHumidity, 1000);
                </script> 
            </head> 
            <body> 
                <h1> IOT Page </h1>
                <h2>Light control</h2>
                <div class="Interactive">
                    <form action="/" method="post">
                        <p><button class="ledButton" type="submit" name="LED_ON" value="on">ON</button></p>
                        <p><button class="ledButton" type="submit" name="LED_OFF" value="off">OFF</button></p>
                    </form>
                </div>
                <br><br>
                <h2>Evironment</h2>
                <div class="Evironment">
                    <div class="Interactive"><h3>Temperature</h3><p id="temperature"></p></div>
                    <div class="Interactive"><h3>Humidity</h3><p id="humidity"></p></div>
                </div> 
                <br><br>
                <h2>Messages for MCU</h2>
                <div class="Interactive">
                    <form id="msgForm" onsubmit="sendMsg(event) ">
                        <h3>Message</h3>
                        <p><input type="text" id="client" name="clientMsg" ></p>
                        <p><button class="submitButton" type="submit">Send</button></p>
                    </form>
                </div>
                <br><br>
                <h2>Messages from MCU</h2>
                <div class="Interactive"><h3>Received</h3><p id="received"></p></div>
            </body> 
        </html>
    )");

    return page;
}

#endif