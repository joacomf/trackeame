#ifndef GESTORDECREDENCIALES_H
#define GESTORDECREDENCIALES_H

#include "Credencial.hpp"
#include <BluetoothSerial.h>

using namespace std;

class GestorDeCredenciales {
    public:
        GestorDeCredenciales();
        vector<Credencial*> obtenerCredenciales();
    private:
        BluetoothSerial bluetoothSerial;
        vector<string> separarCsvDeCredenciales(string csv);
};

#endif