#include <Arduino.h>
#include "ManejadorDeArchivos.hpp"
#include "GestorDeEnvios.hpp"

#include "GestorDeCredenciales.hpp"
#include "GestorDeConexiones.hpp"
#include "Posicionador.hpp"

ManejadorDeArchivos* manejador;
GestorDeEnvios* gestorDeEnvios;
GestorDeCredenciales* gestorDeCredenciales;
GestorDeConexiones* gestorDeConexiones;
vector<Credencial*> credenciales;
Posicionador* posicionador;

void setup(){
    Serial.begin(115200);
    manejador = new ManejadorDeArchivos();
    gestorDeEnvios = new GestorDeEnvios();
    gestorDeCredenciales = new GestorDeCredenciales();
    credenciales = gestorDeCredenciales->obtenerCredenciales();
    gestorDeConexiones = new GestorDeConexiones(credenciales);
    posicionador = new Posicionador();
}

void loop(){
    string proximoArchivoParaEnviar = manejador->obtenerProximoArchivoParaEnviar();
    bool estaConectado = true;
    bool pudoEnviar = true;
    while (estaConectado && proximoArchivoParaEnviar != "" && pudoEnviar) {
        gestorDeConexiones->buscarRedesYConectar();
        estaConectado = gestorDeConexiones->estaConectado();

        if(estaConectado){
            String contenido = manejador->obtenerContenido(proximoArchivoParaEnviar.c_str());
            pudoEnviar = gestorDeEnvios->enviar(contenido);
            if(pudoEnviar) {
                manejador ->eliminar(proximoArchivoParaEnviar);
            }
        }

        proximoArchivoParaEnviar = manejador->obtenerProximoArchivoParaEnviar();
    }
    gestorDeConexiones->desconectar();

    vector <string> posiciones = posicionador->obtenerPaqueteDePosiciones();
    manejador->escribir(posiciones);

}