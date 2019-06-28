#include <Arduino.h>
#include <WiFi.h>
#include "GestorDeConexiones.hpp"

GestorDeConexiones::GestorDeConexiones(vector<Credencial*> credenciales) {
    this->credenciales = credenciales;
    this->desconectar();
    WiFi.mode(WIFI_STA);
}

void GestorDeConexiones::buscarRedesYConectar() {
    Serial.print("Cantidad de credenciales:");
    Serial.println(credenciales.size());

    vector<string> redesDisponibles = obtenerRedesDisponibles();

    intentarConectarConCredencialesGuardadas(redesDisponibles);

}

void GestorDeConexiones::intentarConectarConCredencialesGuardadas(vector<string> redesDisponibles){
    int i = 0;

    while (i < credenciales.size() && !estaConectado()) {
        Credencial* credencial = credenciales[i];
        intentarConectarConRedesDisponibles(redesDisponibles, credencial);
        i++;
    }
}

void GestorDeConexiones::intentarConectarConRedesDisponibles(vector<string> redesDisponibles, Credencial* credencial) {
    int cantidadDeRedesDisponibles = redesDisponibles.size();
    string redGuardada = credencial->ssid();
    string password = credencial->password();

    Serial.print("Red guardada de credencial:");
    Serial.println(redGuardada.c_str());
    Serial.print("Password de credencial:");
    Serial.println(password.c_str());

    int j = 0;
    while (j < cantidadDeRedesDisponibles && !estaConectado()) {
        string redSeleccionada = redesDisponibles[j];

        if (redGuardada == redSeleccionada) {
            conectarConRed(redGuardada, password);
        }
        j++;
    }
}

void GestorDeConexiones::desconectar(){
    WiFi.disconnect();
}

void GestorDeConexiones::conectarConRed(string redGuardada, string password) {
    int cantidadDeIntentos = 0;
    WiFi.begin(redGuardada.c_str(), password.c_str());

    while (!estaConectado() &&
        cantidadDeIntentos++ <= CANTIDAD_DE_INTENTOS_MAXIMA) {

        Serial.print("Conectando a ");
        Serial.println(redGuardada.c_str());
        delay(1000);
    }

    if (estaConectado()) {
        Serial.print("Conectado a ");
        Serial.println(redGuardada.c_str());
    } else {
        Serial.println("No se pudo conectar.");
    }
}

int GestorDeConexiones::obtenerCantidadDeRedesDisponibles() {
    int cantidadDeRedesDisponibles = -1;
    while(cantidadDeRedesDisponibles < 0){
        cantidadDeRedesDisponibles = WiFi.scanNetworks();
    }

    return cantidadDeRedesDisponibles;
}

vector<string> GestorDeConexiones::obtenerRedesDisponibles() {
    int cantidadDeRedesDisponibles = obtenerCantidadDeRedesDisponibles();

    Serial.println("Buscando Access Points...");
    Serial.print("Cantidad de APs:");
    Serial.println(cantidadDeRedesDisponibles);
    vector<string> redesDisponibles;

    for (int i = 0; i < cantidadDeRedesDisponibles; i++) {
        string ssidAP = WiFi.SSID(i).c_str();
        redesDisponibles.push_back(ssidAP);
        //Serial.print("SSID:");
        //Serial.println(ssidAP.c_str());
    }

    return redesDisponibles;
}

bool GestorDeConexiones::estaConectado() {
    Serial.println(WiFi.status());
    return WiFi.status() == WL_CONNECTED;
}