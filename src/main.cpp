#include <Arduino.h>
//#include "ManejadorDeArchivos.hpp"
//#include "GestorDeEnvios.hpp"
#include "GestorDeCredenciales.hpp"
//#include "Posicionador.hpp"

//ManejadorDeArchivos* manejador;
//GestorDeEnvios* gestorDeEnvios;
GestorDeCredenciales* gestorDeCredenciales;
//Posicionador* posicionador;

void setup(){
    Serial.begin(115200);
    //manejador = new ManejadorDeArchivos();
    //gestorDeEnvios = new GestorDeEnvios();
    gestorDeCredenciales = new GestorDeCredenciales();
    gestorDeCredenciales->obtenerCredenciales();
    //posicionador = new Posicionador();
}

void loop(){
    gestorDeCredenciales->conectar();
    /*vector <string> posiciones = posicionador->obtenerPaqueteDePosiciones();
    manejador->escribir(posiciones);

    String contenido = manejador->obtenerContenido("/data.csv");
    gestor->enviar(contenido);*/
}