#ifndef POSICIONADOR_H
#define POSICIONADOR_H

#include <Arduino.h>
#include <bits/stdc++.h> 
#include <math.h>

using namespace std;

class Posicionador{
    public:
        Posicionador();
        vector<string> obtenerPaqueteDePosiciones();
    private:
        double distanciaEnMetrosEntre(double latitud_1, double longitud_1, double latitud_2, double longitud_2);
        double transformarPosicionAGrados(double posicion);
};

#endif