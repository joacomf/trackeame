#include <Arduino.h>
#include <WiFi.h>

void setup(){
  Serial.begin(115200);
}
 
void loop(){
  Serial.println("Start scan");
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    if(WiFi.SSID(i) == "Moto"){
      WiFi.begin("Moto","12345678");
      if(WiFi.status() == WL_CONNECTED){
        Serial.println("Conectado a "+ WiFi.SSID(i));
      }
    } else if(WiFi.SSID(i) == "AP2"){
      WiFi.begin("AP2","password");
      if(WiFi.status() == WL_CONNECTED){
        Serial.println("Conectado a "+ WiFi.SSID(i));
      }
    }
  }
  delay(5000);
  }

  
