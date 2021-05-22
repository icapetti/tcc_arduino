#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

//int counter = 0;

//Estrutura com os dados que serao enviados
typedef struct {
  int idsensor;
  int leitura;
  int nivel;
}Dados;

Dados dados;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receive");

  // Configure LoRa module to transmit and receive at 915MHz (915*10^6) 
  // Replace 915E6 with the frequency you need (eg. 433E6 for 433MHz)
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

    //RECEBER
  
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
    // received a packet
    Serial.println("Received packet ");

    // read packet
    while (LoRa.available()) {
      //Serial.print((char)LoRa.read());
      LoRa.readBytes((uint8_t *)&dados, packetSize);
      /*Serial.print("idsensor: ");
      Serial.println(String(dados.idsensor));
      Serial.print("leitura ");
      Serial.println(dados.leitura);
      Serial.print("nivel ");
      Serial.println(dados.nivel);*/

      String json = "{\"idsensor\":";
      json += dados.idsensor;
      json += ",";
      json += "\"leitura\":";
      json += dados.leitura;
      json += ",";
      json += "\"nivel\":"; 
      json += dados.nivel;
      json += "}*";

      Serial1.println(json);
      Serial.println(json);
      
    }

    // print RSSI of packet
    //Serial.print(" with RSSI ");
    //Serial.println(LoRa.packetRssi());
  }
  
    //delay(500);
}
