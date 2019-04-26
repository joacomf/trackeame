#include <Arduino.h>
#include "SD.h"
#include <SPI.h>
#include "ManejadorDeArchivos.hpp"

ManejadorDeArchivos* manejador;

void setup(){
    Serial.begin(115200);
    String buffer[] = {"Linea;1;datos", "Linea;2;datos", "Linea;3;datos"};
    int longitudBuffer = sizeof(buffer)/sizeof(String);
    Serial.println(longitudBuffer);
    manejador = new ManejadorDeArchivos();
    manejador->escribir(buffer, longitudBuffer);
}

void loop(){}