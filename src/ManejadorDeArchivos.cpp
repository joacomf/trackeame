#include <Arduino.h>
#include "ManejadorDeArchivos.hpp"
#include "SD.h"
#include <SPI.h>

// Define CS pin for the SD card module
#define SD_CS 5

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
    
}

void ManejadorDeArchivos::escribir(String buffer[], int longitud){
    File file = SD.open("/data.csv", FILE_APPEND);
    bool escrituraSatisfactioria = true;
    if(!file) {
        Serial.println("Fallo al abrir archivo para append");
        return;
    }
    for (int i = 0; i < longitud; i++){
        if(!file.println(buffer[i])) {
            escrituraSatisfactioria = false;
        }    
    }
    if(!escrituraSatisfactioria){
        Serial.println("Hubo fallo en la escritura de alguna linea");
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
    String directorioDestino = "/listo/" + nombreDestino;
    File archivoDestino = SD.open(directorioDestino, FILE_WRITE);

    while (archivoOrigen.available()){
        archivoDestino.println(archivoOrigen.readStringUntil('\n'));
    }

    archivoDestino.close();
    archivoOrigen.close();
    this->reiniciarArchivoDeDatos();
}

void ManejadorDeArchivos::reiniciarArchivoDeDatos(){
    SD.remove("/data.csv");
    File archivo = SD.open("/data.csv", FILE_READ);
    archivo.close();
}