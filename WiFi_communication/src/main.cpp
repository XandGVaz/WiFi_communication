#include "header.h"

// Conexão com rede WifFi
void WiFiConnect(){
    // Desconexão de uma rede anterior
    WiFi.disconnect();

    // Configura ESP32 como extação de WiFi sem desabilitar demais modos
    // WiFi.config(LocalIP, Gateway, Subnet);
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
    Serial.print("\nConnect with IP addres: ");
    Serial.println(WiFi.localIP());
}

// Lida com comandos de acendimento de led da página 
void handleBlink(){
  if(Server.arg("LED_ON") == "on")
      digitalWrite(PIN_LED, HIGH);

  if(Server.arg("LED_OFF") == "off")
      digitalWrite(PIN_LED, LOW);
}

// Lida com comandos de submissão da paǵina
void handleSubmit(){
    if(Server.hasArg("clientMsg")){
        Serial.print("Received: ");
        Serial.println(Server.arg("clientMsg"));
    }
}

// Lida com a criação da página raíz
void handleRoot(){
  
  // Caso algum botão tenha sido apertado
  if(Server.hasArg("LED_ON") || Server.hasArg("LED_OFF"))
    handleBlink();
  
  // Caso alguma mensagem tenha sido enviada
  if(Server.hasArg("clientMsg"))
    handleSubmit();

  Server.send(200, "text/html"/*texto do tipo html*/, getPage());
}

// Função que atualiza dados enviados do servidor para o cliente
void handleUpdate(){
  Server.send(200, "text/plain"/*texto normal*/, Sended);
}

// Criação do Server
void createServer(){
  Server.on("/", handleRoot);
  Server.on("/update", handleUpdate);
  Server.begin();
  Serial.println("HTTP Server started!");
  Serial.println("\nChat:");
}

// Função que lida com as solicitações do cliente
void handleClient(){
  Server.handleClient();
}

// Função responsável por definir o dado (do monitor Serial) a ser enviado para o cliente
void sendData(){ 

  // configura dado a ser enviado
  Sended = Serial.readString();
  Sended.replace("\n", "");
  Sended.replace("\r", "");

  // Imprime dado no monitor serial
  Serial.println("Send: " + Sended);
}

void setup() {

  // Condigura pino do led como saída do sistema
  pinMode(PIN_LED, OUTPUT);

  // Configuração do monitor serial
  Serial.begin(115200);

  // Conexão com rede WiFi
  WiFiConnect();

  // Criação do Server dentro da rede WiFi
  createServer();
}

void loop() {

  // verifica se há requisições de novos clientes e configura rotas adequadas
  handleClient();

  // Se ouver dados do serial, são lidos e transmitidos para página HTML
  if(Serial.available()){
    sendData();  
  }

  delay(100);
}
