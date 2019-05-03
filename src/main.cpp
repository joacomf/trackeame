#include <Arduino.h>
#include "SD.h"
#include <SPI.h>
#include "ManejadorDeArchivos.hpp"

ManejadorDeArchivos* manejador;

void setup(){
    Serial.begin(115200);

    manejador = new ManejadorDeArchivos();
}

void loop(){
    String buffer[5];

    for(int i=0;i<5;i++){
        buffer[i] = millis();
    }

    int longitudBuffer = sizeof(buffer)/sizeof(String);
    manejador->escribir(buffer, longitudBuffer);

    delay(200);
}