#include "header.h"

// Conexão com rede WifFi
void WiFiConnect(){
    // Desconexão de uma rede anterior
    WiFi.disconnect();

    // Configura ESP32 como extação de WiFi sem desabilitar demais modos
    WiFi.enableSTA(true);
    delay(2000);

    // Conexão com roteador
    Serial.print("Connect with WiFI ");
    WiFi.begin(ssidRounter, passwordRounter);
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    // Conexão concluída
    Serial.print("Connect with IP addres: ");
    Serial.println(WiFi.localIP());
}

// Lida com comandos de acendimento de led da página 
void handleBlink(){
  if(server.arg("LED_ON") == "on")
      digitalWrite(PIN_LED, HIGH);

  if(server.arg("LED_OFF") == "off")
      digitalWrite(PIN_LED, LOW);
}

// Lida com comandos de submissão da paǵina
void handleSubmit(){
    if(server.hasArg("clientMsg")){
        Serial.print("Usuário: ");
        Serial.println(server.arg("clientMsg"));
    }
}

// Lida com a criação da página raíz
void handleRoot(){
  
  // Caso algum botão tenha sido apertado
  if(server.hasArg("LED_ON") || server.hasArg("LED_OFF"))
    handleBlink();
  
  // Caso alguma mensagem tenha sido enviada
  if(server.hasArg("clientMsg"))
    handleSubmit();

  server.send(200, "text/html", getPage(output));
}

// Criação do server
void createServer(){
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started!");
}

void setup() {

  // Condigura pino do led como saída do sistema
  pinMode(PIN_LED, OUTPUT);

  // Configuração do monitor serial
  Serial.begin(115200);

  // Conexão com rede WiFi
  WiFiConnect();

  // Criação do server dentro da rede WiFi
  createServer();
}

void loop() {
  
  // verifica se há requisições de novos clientes e configura rotas adequadas
  server.handleClient();

  // Se ouver dados do serial, são lidos e transmitidos para página HTML
  if(Serial.available()){
    output = Serial.readString();
    Serial.println("Enviado: " + output);
  }

  delay(100);
}
