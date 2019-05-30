#include "Posicionador.hpp"

#define RXD2 16
#define TXD2 17

Posicionador::Posicionador(){
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

vector<string> Posicionador::obtenerPaqueteDePosiciones(){
    vector <string> buffer;

    Serial.println("Inicio carga");
    while (Serial2.available() && buffer.size() < 10){
        string localizacion = Serial2.readStringUntil('\n').c_str();
        if (localizacion.substr(0,6) == "$GPRMC"){
            Serial.println(localizacion.c_str());
            buffer.push_back(localizacion);
        }
    }

    return buffer;
}