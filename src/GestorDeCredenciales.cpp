#include <Arduino.h>
#include "GestorDeCredenciales.hpp"

GestorDeCredenciales::GestorDeCredenciales() {
    bluetoothSerial.begin("trackeame_bt");
    Serial.println("Bluetooth esta listo");
}

vector<Credencial*> GestorDeCredenciales::obtenerCredenciales() {

    while (!bluetoothSerial.available()) {
        delay(1000);
    }
    
    vector<Credencial*> credenciales;
    string datosRecibidos = bluetoothSerial.readStringUntil('\r').c_str();
    bluetoothSerial.end();
    vector<string> credencialesCsv = separarCsvDeCredenciales(datosRecibidos);

    for (int i = 0; i < credencialesCsv.size(); i++) {
        string credencialCsv = credencialesCsv[i];
        char* ssid = strtok((char*)credencialCsv.c_str(), ",");
        char* password = strtok(NULL, ",");
        Credencial* credencial = new Credencial(ssid, password);
        credenciales.push_back(credencial);
        Serial.print("SSID:");
        Serial.println(ssid);
        Serial.print("Password:");
        Serial.println(password);
    }

    return credenciales;
}

vector<string> GestorDeCredenciales::separarCsvDeCredenciales(string csv) {
    vector<string> credencialesCsv;
    char* credencial = strtok((char*)csv.c_str(), ";");
    Serial.print("Received:");
    Serial.println(csv.c_str());

    while (credencial != NULL) {
        credencialesCsv.push_back(credencial);
        credencial = strtok(NULL, ";");
    }

    return credencialesCsv;
}