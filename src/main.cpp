#include <Arduino.h>
#include "ManejadorDeArchivos.hpp"
#include "GestorDeEnvios.hpp"
#include "Posicionador.hpp"

ManejadorDeArchivos* manejador;
GestorDeEnvios* gestor;
Posicionador* posicionador;

void setup(){
    Serial.begin(115200);
    manejador = new ManejadorDeArchivos();
    gestor = new GestorDeEnvios();
    posicionador = new Posicionador();
}

void loop(){
    vector <string> posiciones = posicionador->obtenerPaqueteDePosiciones();

    manejador->escribir(posiciones);

    string proximoArchivoParaEnviar = manejador->obtenerProximoArchivoParaEnviar();
    while (proximoArchivoParaEnviar != "") {
        String contenido = manejador->obtenerContenido(proximoArchivoParaEnviar.c_str());
        gestor->enviar(contenido);

        proximoArchivoParaEnviar = manejador->obtenerProximoArchivoParaEnviar();
    }

}