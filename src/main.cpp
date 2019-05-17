#include <Arduino.h>
#include "ManejadorDeArchivos.hpp"
// #include "GestorDeEnvios.hpp"
#include "Posicionador.hpp"

ManejadorDeArchivos* manejador;
// GestorDeEnvios* gestor;
Posicionador* posicionador;

void setup(){
    Serial.begin(115200);
    manejador = new ManejadorDeArchivos();
    //gestor = new GestorDeEnvios();
    posicionador = new Posicionador();
}

void loop(){
    vector <string> posiciones = posicionador->obtenerPaqueteDePosiciones();
    manejador->escribir(posiciones);

    //String contenido = manejador->obtenerContenido("/data.csv");
    //gestor->enviar(contenido);
}