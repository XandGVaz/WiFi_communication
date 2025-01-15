#include "header.h"

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

/*===============================================================================*/
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
    String received;
    if(Server.hasArg("clientMsg")){
      received = Server.arg("clientMsg");
      updateValueLCD(received);

      Serial.println(F("------------------------------------"));
      Serial.print("Received: ");
      Serial.println(received);
      
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
void handleUpdateReceived(){
  Server.send(200, "text/plain"/*texto normal*/, Sended);
}

// Função que atualiza dados enviados do servidor para o cliente
void handleUpdateTemp(){
  updateValueDHT();
  Server.send(200, "text/plain"/*texto normal*/, Temperature);
}

// Função que atualiza dados enviados do servidor para o cliente
void handleUpdateHum(){
  updateValueDHT();
  Server.send(200, "text/plain"/*texto normal*/, Humidity);
}

// Criação do Server
void createServer(){
  Server.on("/", handleRoot);               // lida com atualização de página
  Server.on("/received", HTTP_GET, handleUpdateReceived);     // lida com atualização de dado recebido pelo cliente
  Server.on("/temp", HTTP_GET, handleUpdateTemp);     // lida com atualização da temperatura ambiente
  Server.on("/hum", HTTP_GET ,handleUpdateHum);       // lida com atualização da humdiade do ambiente
  Server.begin();                           // inicia server

  // Avisa que server começou
  Serial.println("HTTP Server started!");
  Serial.println(F("\n===================================="));
  Serial.println("Chat:");
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
  Serial.println(F("------------------------------------"));
  Serial.println("Send: " + Sended);
}

/*===============================================================================*/
// Função responsável por configurar o sensor DHT
void setupDHT(){
  // Iniciação do sensor DHT
  DHT.begin();
  DHT.temperature().getSensor(&Sensor);
  DHT.humidity().getSensor(&Sensor);
}

// Função que lê informações do sensor e atualizar dados de temperatura e umidade
void updateValueDHT(){
  
  sensors_event_t event;                          // evento de sensoriamento
  float temperature, humidity;                    // armazena valores numéricos

  // Obtenção da temperatura
  DHT.temperature().getEvent(&event);
  if(isnan(event.temperature)) temperature = -1;  // verifica erros
  else temperature = event.temperature;

  // Obtenção da umidade
  DHT.humidity().getEvent(&event);
  if(isnan(event.relative_humidity)) humidity = -1;// verifica erros
  else humidity = event.temperature;

  // Atualização dos dados de temperatura e umidade
  Temperature = String(temperature); Humidity = String(humidity);
}

/*===============================================================================*/

// Função responssável por testar a conexão de um endereço (verificando se ele existe)
bool I2CAddrTest(byte addr){
  // Começa transmissão de barramento com o endereço passado por parâmetro
  Wire.beginTransmission(addr);
  
  // Se a transmissão ocorrer automaticamente, o endereço existe
  if(Wire.endTransmission() == 0);
    return true;
  
  // Caso contrário (demorou mais tempo para término da transmissão), o endereço não existe
  return false;
}

// Configuração do display LCD1602
void setupLCD(){
  // Barramento de dados + controle
  Wire.begin(SDA, SCL); // necessário para o funcionamento da biblioteca LiquidCrystal_I2C 

  // Caso o endereço do CI não exista no lcd, então trocamos de endereço
  if(!I2CAddrTest(CI_ADDR1))
    lcd = LiquidCrystal_I2C(CI_ADDR2, 16, 2);

  // Iniciação do driver do LCD
  lcd.init();

  // Abre luz de fundo do LCD
  lcd.backlight();
}

void updateValueLCD(String value){

  // Limpa tela do LCD
  lcd.clear();

  // Seta a posição de impressão no lcd no início da primeira linha
  lcd.setCursor(0,0);

  // Impressão de dado que cabe na primeira linha do LCD
  if(value.length() <= 10){         
    lcd.print("Usr: " + value);
    return ;
  }

  // Impressão de dados que exigem o uso de duas linhas
  lcd.print("Usr: " + value.substring(0,11));
  lcd.setCursor(0,1);
  lcd.print(value.substring(11,27));

}
