#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "GestorDeConexiones.hpp"

GestorDeConexiones::GestorDeConexiones(vector<Credencial*> credenciales) {
    this->credenciales = credenciales;
}

void GestorDeConexiones::conectar() {
    buscarRedesYConectar();
    Serial.print("Cantidad de credenciales:");
    Serial.println(credenciales.size());
}

void GestorDeConexiones::buscarRedesYConectar() {
    vector<string> redesDisponibles = obtenerRedesDisponibles();

    intentarConectarARedesDisponibles(redesDisponibles);
}

void GestorDeConexiones::intentarConectarARedesDisponibles(vector<string> redesDisponibles){
    int i = 0;
    int cantidadDeRedesDisponibles = redesDisponibles.size();

    while (i < credenciales.size() && !estaConectado()) {
        Credencial* credencial = credenciales[i];
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

            j++;
        }

        i++;
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