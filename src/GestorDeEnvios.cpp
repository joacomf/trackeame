#include <Arduino.h>
#include "GestorDeEnvios.hpp"
#include <HTTPClient.h>
#include <WiFi.h>


GestorDeEnvios::GestorDeEnvios(){
    WiFi.begin("Moto", "12345678"); 
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando");
    }
    Serial.println("Conectado");
}

void GestorDeEnvios::enviar(String contenidoArchivo){
    if(WiFi.status() == WL_CONNECTED){
         this->cliente.begin("http://jsonplaceholder.typicode.com/posts");
         this->cliente.addHeader("Content-Type", "text/plain");
         int codigoHTTPRespuesta = this->cliente.POST(contenidoArchivo);
         if(codigoHTTPRespuesta > 0){
             String respuesta = this->cliente.getString();
             Serial.println(respuesta);
         } else {
             Serial.println(String("Error al enviar"));
         }
    } else {
        Serial.print("No se pudo realizar el envio");
    }
}