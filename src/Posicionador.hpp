#ifndef POSICIONADOR_H
#define POSICIONADOR_H

#include <Arduino.h>
#include <bits/stdc++.h> 

using namespace std;

class Posicionador{
    public:
        Posicionador();
        vector<string> obtenerPaqueteDePosiciones();
};

#endif