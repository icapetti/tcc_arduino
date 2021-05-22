#include <LoRa.h> //biblioteca para LoRa
#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA

int idsensor = 1;

Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

int nivel = 0;
int counter = 0;
int leitura = 0;

//Estrutura com os dados que serao enviados
typedef struct {
  int idsensor;
  int leitura;
  int nivel;
}Dados;

Dados dados;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  // Configure LoRa module to transmit and receive at 915MHz (915*10^6) 
  // Replace 915E6 with the frequency you need (eg. 433E6 for 433MHz)
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
}

void loop() {

    Serial.print("Pressure = ");
    leitura = bmp.readPressure();
    Serial.print(leitura);
    Serial.println(" Pa");

    if(leitura <= 94795){
      nivel = 1;
    }else if(leitura > 94795 && leitura <= 74780){
      nivel = 2;
    }else if(leitura > 94780){
      nivel = 3;
    }

    dados.idsensor = idsensor;
    dados.leitura = leitura;
    dados.nivel = nivel;

    //ENVIAR
    Serial.print("Sending packet: ");
    Serial.println(counter);
  
    // send packet
    LoRa.beginPacket();
    //LoRa.print(dados);
    LoRa.write((uint8_t*)&dados, sizeof(dados));
    LoRa.endPacket();

    counter++;
    
    delay(5000);
}
