#include <Arduino.h>
#include "GestorDeEnvios.hpp"
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

GestorDeEnvios::GestorDeEnvios(){
    this->conectar();
}

bool GestorDeEnvios::enviar(String contenidoArchivo){
    bool pudoEnviar = false;
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
        pudoEnviar = codigoHTTPRespuesta == 200;

        if(!pudoEnviar){
            String respuesta = this->cliente.getString();
            Serial.println(String("Error al enviar"));
            Serial.println(respuesta);
            Serial.println(codigoHTTPRespuesta);
        }
    } else {
        Serial.print("No se pudo realizar el envio");
    }

    return pudoEnviar;
}

bool GestorDeEnvios::estaConectado(){
    return WiFi.status() == WL_CONNECTED;
}

bool GestorDeEnvios::conectar(){
    WiFi.begin("Fibertel WiFi190 2.4GHz", "telecomunicaciones96");

    bool estaConectado = WiFi.status() == WL_CONNECTED;
    int numeroDeIntentos = 0;

    while (!estaConectado && numeroDeIntentos < CANTIDAD_DE_INTENTOS_MAXIMA) {
        delay(1000);
        Serial.println("Conectando");

        estaConectado = WiFi.status() == WL_CONNECTED;
        numeroDeIntentos++;
    }

    Serial.println("Conectado");

    return estaConectado;
}