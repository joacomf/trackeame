#include <Arduino.h>
#include "GestorDeEnvios.hpp"
#include <HTTPClient.h>
#include <WiFi.h>


GestorDeEnvios::GestorDeEnvios(){
    WiFi.begin("SSID", "password"); 
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando");
    }
    Serial.println("Conectado");
}

void GestorDeEnvios::enviar(String contenidoArchivo){
    if(WiFi.status() == WL_CONNECTED){
        //this->cliente.begin("http://jsonplaceholder.typicode.com/posts");
        this->cliente.begin("http://192.168.0.186:5000/api/locations");
        this->cliente.addHeader("Content-Type", "text/json");
        int codigoHTTPRespuesta = this->cliente.POST("{content: " + contenidoArchivo +"}");
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