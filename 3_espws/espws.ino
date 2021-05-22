#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define WIFI_RETRY_DELAY 200

WiFiClient wifiClient;
HTTPClient http;

void setup() {
  Serial.begin(9600);


  WiFi.mode(WIFI_STA);
  WiFi.begin("HSHO" , "tccdevoces");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(WIFI_RETRY_DELAY);
        Serial.println("Trying to connect to wifi...");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("\n** Connected to WIFI");
        Serial.print(", IP: ");
        Serial.println(WiFi.localIP());
    }
    else {
        Serial.print("** Error connecting to wifi");
    }

}


String inString = "";


void loop() {

  while (Serial.available() > 0) {
    int inChar = Serial.read();

    if (inChar != '*') {
      inString += (char)inChar;
    }

    if(inChar == '*') {
      Serial.println(inString);

        http.begin("http://192.168.43.13:80/tcc_ws/gravar_leitura.php");
        http.addHeader("Content-Type", "text/plain");
        int httpCode = http.POST(inString);
        
        
      
      inString = "";
    }
  }
}
