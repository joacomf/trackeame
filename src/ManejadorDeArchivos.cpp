#include <Arduino.h>
#include "ManejadorDeArchivos.hpp"
#include "SD.h"
#include <SPI.h>

#define SD_CS 5
#define BYTES_POR_ARCHIVO 21000

ManejadorDeArchivos::ManejadorDeArchivos(){
    bool tarjetaInicializada = SD.begin(SD_CS);  
    if(!tarjetaInicializada) {
        Serial.println("Falló el montado de la tarjeta SD");
        return;
    }
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE) {
        Serial.println("No hay tarjeta SD");
        return;
    }
    //Crea el archivo de almacenamiento de posiciones (si no existe)
    if(!SD.exists("/data.csv")){
        File file = SD.open("/data.csv", FILE_WRITE);
        file.close();
    }
    SD.mkdir("/listo");
}

bool ManejadorDeArchivos::escribir(vector<string> posiciones){
    File file = SD.open("/data.csv", FILE_APPEND);

    bool archivoLleno = false;

    if(!file) {
        Serial.println("Fallo al abrir archivo para append");
        return false;
    }

    vector<string>::iterator iterador;
    for (iterador = posiciones.begin(); iterador != posiciones.end(); ++iterador){
        if(file.size() < BYTES_POR_ARCHIVO){
            string posicion = *iterador;
            file.println(posicion.c_str());
        }else{
            file.close();
            this->disponibilizarParaTransferencia(String(millis()));
            file = SD.open("/data.csv", FILE_APPEND);

            archivoLleno = true;
        }
    }

    Serial.println("Escritura satisfactoria");
    file.close();

    return archivoLleno;
}

void ManejadorDeArchivos::listarArchivos(){
    File root = SD.open("/");
    while(File entry = root.openNextFile()){
        Serial.println(entry.name());
        entry.close();
    }
    root.close();
}

void ManejadorDeArchivos::disponibilizarParaTransferencia(String nombreDestino){
    File archivoOrigen = SD.open("/data.csv", FILE_READ);
    String directorioDestino = String("/listo/") + nombreDestino + String(".csv");
    File archivoDestino = SD.open(directorioDestino, FILE_WRITE);

    while (archivoOrigen.available()){
        archivoDestino.println(archivoOrigen.readStringUntil('\n'));
    }

    archivoDestino.close();
    archivoOrigen.close();
    this->reiniciarArchivoDeDatos();
}

String ManejadorDeArchivos::obtenerContenido(String nombreArchivo){
    String contenido = "";
    File archivoOrigen = SD.open(nombreArchivo, FILE_READ);
    while (archivoOrigen.available()){
        contenido += archivoOrigen.readStringUntil('\n') + '\n';
    }
    return contenido;
}

void ManejadorDeArchivos::reiniciarArchivoDeDatos(){
    SD.remove("/data.csv");
    File archivo = SD.open("/data.csv", FILE_WRITE);
    archivo.close();
}