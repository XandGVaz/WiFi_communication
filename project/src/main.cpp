#include "header.hpp"

/*===============================================================================*/

void setup() {

  // Configura pino do led como saída do sistema
  pinMode(PIN_LED, OUTPUT);

  // Configura sensor DHT
  setupDHT();

  // Configura LCD1602
  setupLCD();

  // Configuração do monitor serial
  Serial.begin(115200);

  // Conexão com rede WiFi
  WiFiConnect();

  // Criação do Server dentro da rede WiFi
  createServer();
}

void loop() {

  // Verifica se há requisições de novos clientes e configura rotas adequadas
  handleClient();

  // Se ouver dados do serial, são lidos e transmitidos para página HTML
  if(Serial.available()){
    sendData();  
  }

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
