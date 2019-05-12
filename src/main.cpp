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
    String buffer[] = {"hola", "prueba", "prueba2"};
    manejador->escribir(buffer, 3);
    String contenido = manejador->obtenerContenido("/data.csv");
    gestor->enviar(contenido);
    delay(5000);
}