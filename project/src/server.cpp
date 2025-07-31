/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a implementação da criação e administração do server .
 * Data: 31/07/2025
 */

#define DEF_MOD_SERVER
#include "server.hpp"
#define DEF_MOD_DHT
#include "dht.hpp"
#define DEF_MOD_DISPLAY
#include "display.hpp"
#include "light.hpp"
#include "html.hpp"

/*===============================================================================*/
// Funções do servidor

// Cria objeto server
void setupServer(){
  Server = new WebServer(80);
}

// Conexão com rede WifFi
void WiFiConnect(){
    // Desconexão de uma rede anterior
    WiFi.disconnect();

    // Configura ESP32 como extação de WiFi sem desabilitar demais modos
    WiFi.enableSTA(true);
    delay(2000);

    // Conexão com roteador
    Serial.println(F("\n===================================="));
    Serial.print("Connect with WiFI ");
    WiFi.begin(ssidRounter, passwordRounter);
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    // Conexão concluída
    Serial.print("\nConnect with IP addres: ");
    Serial.println(WiFi.localIP());
}

// Lida com comandos de acendimento de luz da página 
void handleLight(){
  if(Server->arg("LED_ON") == "on")
    lightOn();

  if(Server->arg("LED_OFF") == "off")
    lightOff();
}

// Lida com comandos de submissão da paǵina
void handleSubmit(){
    String received;

    // Caso um dado (texto) tenha sido submetido, o mesmo é recebido no serial e no Display1602
    if(Server->hasArg("clientMsg")){
      received = Server->arg("clientMsg");
      updateValueDisplay(received);

      Serial.println(F("------------------------------------"));
      Serial.print("Received: ");
      Serial.println(received);
      
    }
}

// Lida com a criação da página raíz
void handleRoot(){

  if(Server->method() == HTTP_POST){
    // Caso algum botão tenha sido apertado, lida com essa ação
    if(Server->hasArg("LED_ON") || Server->hasArg("LED_OFF"))
      handleLight();

    // Caso alguma mensagem tenha sido enviada, lida-se com esse envio
    if(Server->hasArg("clientMsg"))
      handleSubmit();
  }

  Server->send(200, "text/html"/*texto do tipo html*/, htmlPage);
}

// Função que atualiza dados enviados do servidor para o cliente
void handleUpdateReceived(){
  Server->send(200, "text/plain"/*texto normal*/, Sended);
}

// Função que atualiza dados enviados do servidor para o cliente
void handleUpdateTemp(){
  updateValueDHT();
  Server->send(200, "text/plain"/*texto normal*/, Temperature);
}

// Função que atualiza dados enviados do servidor para o cliente
void handleUpdateHum(){
  updateValueDHT();
  Server->send(200, "text/plain"/*texto normal*/, Humidity);
}

// Função que lida com as solicitações do cliente
void handleClient(){
  Server->handleClient();
}

// Criação do Server
void createServer(){
  Server->on("/", HTTP_GET ,handleRoot);                      // lida com atualização de página
  Server->on("/", HTTP_POST ,handleRoot);                     // lida com atualização de página
  Server->on("/received", HTTP_GET, handleUpdateReceived);    // lida com atualização de dado recebido pelo cliente e enviado pela ESP32
  Server->on("/temp", HTTP_GET, handleUpdateTemp);            // lida com atualização da temperatura ambiente
  Server->on("/hum", HTTP_GET ,handleUpdateHum);              // lida com atualização da humdiade do ambiente
  Server->begin();                                            // inicia o server

  // Avisa que server começou
  Serial.println("HTTP Server started!");
  Serial.println(F("\n===================================="));
  Serial.println("Chat:");
}


// Função responsável por definir o dado (do monitor Serial) a ser enviado para o cliente
void sendData(){ 

  // configura dado a ser enviado
  Sended = Serial.readString();
  Sended.replace("\n", "");
  Sended.replace("\r", "");

  // Imprime dado no monitor serial
  Serial.println(F("------------------------------------"));
  Serial.println("Sended: " + Sended);
}
