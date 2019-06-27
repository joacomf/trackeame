#include <Arduino.h>
//#include "ManejadorDeArchivos.hpp"
//#include "GestorDeEnvios.hpp"
#include "GestorDeCredenciales.hpp"
#include "GestorDeConexiones.hpp"
//#include "Posicionador.hpp"

//ManejadorDeArchivos* manejador;
//GestorDeEnvios* gestorDeEnvios;
GestorDeCredenciales* gestorDeCredenciales;
GestorDeConexiones* gestorDeConexiones;
vector<Credencial*> credenciales;
//Posicionador* posicionador;

void setup(){
    Serial.begin(115200);
    //manejador = new ManejadorDeArchivos();
    //gestorDeEnvios = new GestorDeEnvios();
    gestorDeCredenciales = new GestorDeCredenciales();
    credenciales = gestorDeCredenciales->obtenerCredenciales();
    gestorDeConexiones = new GestorDeConexiones(credenciales);
    //posicionador = new Posicionador();
}

void loop(){
    gestorDeConexiones->buscarRedesYConectar();
    /*vector <string> posiciones = posicionador->obtenerPaqueteDePosiciones();
    manejador->escribir(posiciones);

    String contenido = manejador->obtenerContenido("/data.csv");
    gestor->enviar(contenido);*/
}