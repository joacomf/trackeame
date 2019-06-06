#include "Posicionador.hpp"

#define RXD2 16
#define TXD2 17

#define d2r (M_PI / 180.0)

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

double Posicionador::distanciaEnMetrosEntre(double latitud_1, double longitud_1, double latitud_2, double longitud_2){
    
    double diferenciaLongitud = (longitud_2 - longitud_1) * d2r;
    double diferenciaLatitud = (latitud_2 - latitud_1) * d2r;
    double a = pow(sin(diferenciaLatitud/2.0), 2) + cos(latitud_1*d2r) * cos(latitud_2*d2r) * pow(sin(diferenciaLongitud/2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distanciaEnMetros = 6371000 * c;

    return distanciaEnMetros;
}

double Posicionador::transformarPosicionAGrados(double posicion){
    double longitudDecimal = (posicion / 100.0);
    int grados = (int) longitudDecimal;

    double resto = (longitudDecimal - grados) * 100.0 / 60;

    return (grados + resto);
}
