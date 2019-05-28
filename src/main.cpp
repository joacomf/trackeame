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
    while (gestor->estaConectado() && proximoArchivoParaEnviar != "") {
        String contenido = manejador->obtenerContenido(proximoArchivoParaEnviar.c_str());

        bool seEnvioElArchivoCorrectamente = gestor->enviar(contenido);
        if(seEnvioElArchivoCorrectamente) {
            manejador->eliminar(proximoArchivoParaEnviar);
        }

        proximoArchivoParaEnviar = manejador->obtenerProximoArchivoParaEnviar();
    }

}