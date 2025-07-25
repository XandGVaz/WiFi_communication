/*
 * Projeto: Comunicação WiFi para IoT
 * Autor: Vitor Alexandre Garcia Vaz
 * Descrição: Este arquivo contém a implementação de utilização do display.
 * Data: 25/07/2025
 */

#include "display.hpp"

/*===============================================================================*/
// Funções do display

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

// Configuração do display 
void setupDisplay(){
  // Criação do objeto Display
  Display = new LiquidCrystal_I2C(CI_ADDR1, 16/*colunas*/, 2/*linhas*/);

  // Barramento de dados + controle
  Wire.begin(SDA, SCL); // necessário para o funcionamento da biblioteca LiquidCrystal_I2C 

  // Caso o endereço do CI não exista no Display, então trocamos de endereço
  if(!I2CAddrTest(CI_ADDR1)){
    delete Display;
    Display = new LiquidCrystal_I2C(CI_ADDR2, 16, 2);
  }

  // Iniciação do driver do Display
  Display->init();

  // Abre luz de fundo do Display
  Display->backlight();
}

// Função que atualiza o valor presente no display, confome o texto passado por parâmetro
void updateValueDisplay(String value){
  // Limpa tela do Display
  Display->clear();

  // Seta a posição de impressão no Display no início da primeira linha
  Display->setCursor(0,0);

  // Impressão de dado que cabe na primeira linha do Display
  if(value.length() <= 10){         
    Display->print("Usr: " + value);
    return ;
  }

  // Impressão de dados que exigem o uso de duas linhas
  Display->print("Usr: " + value.substring(0,11));
  Display->setCursor(0,1);
  Display->print(value.substring(11,27));
}