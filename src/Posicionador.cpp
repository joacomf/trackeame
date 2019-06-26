#include "Posicionador.hpp"

#define RXD2 16
#define TXD2 17
#define CANTIDAD_DE_MUESTRAS_DE_PARADA 60

#define d2r (M_PI / 180.0)

Posicionador::Posicionador(){
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    this->cantidadDeMuestrasSinCambiar = 0;
}

vector<string> Posicionador::obtenerPaqueteDePosiciones(){
    vector <string> buffer;

    Serial.println("Inicio carga");

    while(!Serial2.available()); //Espero a que este disponible (ver si asignar timeout)
    Serial.println("Serial disponible");
    string localizacion = this -> obtenerProximaPosicionValida();
    string latitud = this->obtenerDatoEnPosicion(localizacion, 3);
    string longitud = this->obtenerDatoEnPosicion(localizacion, 5);

    double latitudEnGrados = this->transformarPosicionAGrados(atof(latitud.c_str()));
    double longitudEnGrados = this->transformarPosicionAGrados(atof(longitud.c_str()));
    buffer.push_back(localizacion);

    while (Serial2.available() && buffer.size() < 10){

        string localizacionSiguiente = this -> obtenerProximaPosicionValida();
        string latitudSiguiente = this->obtenerDatoEnPosicion(localizacionSiguiente, 3);
        string longitudSiguiente = this->obtenerDatoEnPosicion(localizacionSiguiente, 5);
        double latitudSiguienteEnGrados = this->transformarPosicionAGrados(atof(latitudSiguiente.c_str()));
        double longitudSiguienteEnGrados = this->transformarPosicionAGrados(atof(longitudSiguiente.c_str()));

        double distancia = this->distanciaEnMetrosEntre(latitudEnGrados, longitudEnGrados, latitudSiguienteEnGrados, longitudSiguienteEnGrados);
        Serial.println(distancia);
        if (distancia > 3) {
            buffer.push_back(localizacionSiguiente);
            this->cantidadDeMuestrasSinCambiar = 0;
        } else {
            this->cantidadDeMuestrasSinCambiar++;

            if (this->cantidadDeMuestrasSinCambiar == CANTIDAD_DE_MUESTRAS_DE_PARADA) {
                string parada = "$PARADA" + localizacionSiguiente.substr(6);
                buffer.push_back(parada);
                this->cantidadDeMuestrasSinCambiar = 0;
            }
        }

        latitudEnGrados = latitudSiguienteEnGrados;
        longitudEnGrados = longitudSiguienteEnGrados;

    }

    return buffer;
}

string Posicionador::obtenerDatoEnPosicion(string localizacion, int posicion){
    char *token = std::strtok((char*) localizacion.c_str(), ",");
    for (int i = 0; i < posicion && token != NULL; i++){
        token = std::strtok(NULL, ",");
    }

    return token;
}

string Posicionador::obtenerProximaPosicionValida(){
    bool posicionValida = false;
    string localizacion;
    Serial.println("Esperando posicion valida");
    while(!posicionValida) {

        localizacion = Serial2.readStringUntil('\n').c_str();

        while(localizacion.substr(0, 6).compare("$GPRMC") != 0){
            localizacion = Serial2.readStringUntil('\n').c_str();
        }

        int indice = localizacion.find_first_of("V");
        if(indice >= localizacion.length() && indice < 0){
            posicionValida = true;
            Serial.println(localizacion.c_str());
        }
    }

    return localizacion;
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
