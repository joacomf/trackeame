#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "GestorDeConexiones.hpp"

GestorDeConexiones::GestorDeConexiones() {}

void GestorDeConexiones::conectar(vector<Credencial*> credenciales) {
    int cantidadDeAPs = WiFi.scanNetworks();
    vector<string> ssidAPs;

    for (int i = 0; i < cantidadDeAPs; i++) {
        string ssidAP = WiFi.SSID(i).c_str();
        ssidAPs.push_back(ssidAP);
    }

    for (int i = 0; i < credenciales.size(); i++) {
        Credencial* credencial = credenciales[i];
        string ssid = credencial->ssid();
        string password = credencial->password();

        for (int j = 0; j < cantidadDeAPs; j++) {
            string ssidAP = ssidAPs[i];

            if (ssid.compare(ssidAP) == 0) {
                WiFi.begin(ssid.c_str(), password.c_str());

                if (WiFi.status() == WL_CONNECTED) {
                    Serial.print("Conectado a ");
                    Serial.println(ssid.c_str());
                    break;
                }
            }
        }
    }
}