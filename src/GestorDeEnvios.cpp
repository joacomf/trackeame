#include <Arduino.h>
#include "GestorDeEnvios.hpp"
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

GestorDeEnvios::GestorDeEnvios(){
    WiFi.begin("Fibertel WiFi190 2.4GHz", "telecomunicaciones96"); 
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando");
    }
    Serial.println("Conectado");
}

void GestorDeEnvios::enviar(String contenidoArchivo){
    DynamicJsonDocument doc(25000);
    if(WiFi.status() == WL_CONNECTED){
        this->cliente.begin("http://192.168.0.186:5000/api/locations");
        this->cliente.addHeader("Content-Type", "application/json");
        String cuerpo = "\"" + contenidoArchivo  + "\"";
        doc["posiciones"] = contenidoArchivo;
        doc["usuario"] = "untref";
        String envio;
        serializeJson(doc, envio);
        int codigoHTTPRespuesta = this->cliente.POST(envio);
        if(codigoHTTPRespuesta > 0){
            String respuesta = this->cliente.getString();
            Serial.println(respuesta);
        } else {
            Serial.println(String("Error al enviar"));
            Serial.println(codigoHTTPRespuesta);
        }
    } else {
        Serial.print("No se pudo realizar el envio");
    }
}