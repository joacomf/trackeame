#ifndef POSICIONADOR_H
#define POSICIONADOR_H

#include <Arduino.h>
#include <bits/stdc++.h> 
#include <math.h>
#include <string.h>

using namespace std;

class Posicionador{
    public:
        Posicionador();
        vector<string> obtenerPaqueteDePosiciones();
    private:
        int cantidadDeMuestrasSinCambiar;
        double distanciaEnMetrosEntre(double latitud_1, double longitud_1, double latitud_2, double longitud_2);
        double transformarPosicionAGrados(double posicion);
        string obtenerDatoEnPosicion(string localizacion, int posicion);
        string obtenerProximaPosicionValida();
        bool cargarLocalizacionEnBufferSegunDistancia(string localizacion, vector<string> &buffer, int distancia);
};

#endif