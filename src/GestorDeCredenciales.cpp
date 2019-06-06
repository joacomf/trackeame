#include <Arduino.h>
#include <string>
#include <HTTPClient.h>
#include <WiFi.h>
#include "GestorDeCredenciales.hpp"

GestorDeCredenciales::GestorDeCredenciales() {
    bluetoothSerial.begin("trackeame_bt");
    Serial.println("Bluetooth Device is Ready to Pair");
}

void GestorDeCredenciales::obtenerCredenciales() {

    while (!bluetoothSerial.available()) {
        delay(1000);
    }
    
    string datosRecibidos = bluetoothSerial.readStringUntil('\r').c_str();
    vector<string> credenciales = convertirDeCsvACredenciales(datosRecibidos);
    Serial.println("Estoy vivo");

    for (int i = 0; i < credenciales.size(); i++) {
        string credencial = credenciales[i];
        char* ssid = strtok((char*)credencial.c_str(), ",");
        char* password = strtok(NULL, ",");
        Serial.print("SSID:");
        Serial.println(ssid);
        Serial.print("Password:");
        Serial.println(password);
        ssids.push_back(ssid);
        passwords.push_back(password);
    }
}

void GestorDeCredenciales::conectar() {
   /* int cantidadDeAPs = WiFi.scanNetworks();
    vector<String> ssidAPs;

    for (int i = 0; i < cantidadDeAPs; i++) {
        String ssidAP = WiFi.SSID(i);
        ssidAPs.push_back(ssidAP);
    }

    for (int i = 0; i < ssids.size(); i++) {
        String ssid = ssids[i].c_str();
        String password = passwords[i].c_str();

        for (int j = 0; j < cantidadDeAPs; j++) {
            String ssidAP = ssidAPs[i];

            if (ssid == ssidAP) {
                WiFi.begin(ssid.c_str(), password.c_str());

                if (WiFi.status() == WL_CONNECTED) {
                    Serial.println("Conectado a " + ssid);
                }
            }
        }
    }*/
}

vector<string> GestorDeCredenciales::convertirDeCsvACredenciales(string csv) {
    vector<string> credenciales;
    char* credencial = strtok((char*)csv.c_str(), ";");
    Serial.print("Received:");
    Serial.println(csv.c_str());

    while (credencial != NULL) {
        credenciales.push_back(credencial);
        credencial = strtok(NULL, ";");
    }

    return credenciales;
}