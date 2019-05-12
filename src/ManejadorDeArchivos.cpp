#include <Arduino.h>
#include "ManejadorDeArchivos.hpp"
#include "SD.h"
#include <SPI.h>

#define SD_CS 5
#define BYTES_POR_ARCHIVO 21000

ManejadorDeArchivos::ManejadorDeArchivos(){
    bool tarjetaInicializada = SD.begin(SD_CS);  
    if(!tarjetaInicializada) {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE) {
        Serial.println("No SD card attached");
        return;
    }
    //Crea el archivo de almacenamiento de posiciones (si no existe)
    if(!SD.exists("/data.csv")){
        File file = SD.open("/data.csv", FILE_WRITE);
        file.close();
    }
    SD.mkdir("/listo");
    
}

void ManejadorDeArchivos::escribir(String buffer[], int longitud){
    File file = SD.open("/data.csv", FILE_APPEND);

    if(!file) {
        Serial.println("Fallo al abrir archivo para append");
        return;
    }

    for (int i = 0; i < longitud; i++){
        if(file.size() < BYTES_POR_ARCHIVO){
            file.println(buffer[i]);
        } else {
            file.close();
            this->disponibilizarParaTransferencia(String(millis()));
            file = SD.open("/data.csv", FILE_APPEND);
        }
    }

    Serial.println("Escritura satisfactoria");
    file.close();
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
    String linea = "";
    File archivoOrigen = SD.open(nombreArchivo, FILE_READ);
    while (archivoOrigen.available()){
        linea = archivoOrigen.readStringUntil('\n');
        contenido = contenido + linea;
    }
    return contenido;
}

void ManejadorDeArchivos::reiniciarArchivoDeDatos(){
    SD.remove("/data.csv");
    File archivo = SD.open("/data.csv", FILE_WRITE);
    archivo.close();
}