#include <Arduino.h>
#include "SD.h"
#include <SPI.h>
#include "ManejadorDeArchivos.hpp"
#include "GestorDeEnvios.hpp"

ManejadorDeArchivos* manejador;
GestorDeEnvios* gestor;

void setup(){
    Serial.begin(115200);
    manejador = new ManejadorDeArchivos();
    gestor = new GestorDeEnvios();
}

void loop(){
    gestor -> enviar("esto es una prueba de envio");
    delay(2000);
}