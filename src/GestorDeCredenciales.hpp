#ifndef GESTORDECREDENCIALES_H
#define GESTORDECREDENCIALES_H

#include <BluetoothSerial.h>

using namespace std;

class GestorDeCredenciales {
    public:
        GestorDeCredenciales();
        void obtenerCredenciales();
        void conectar();
    private:
        BluetoothSerial bluetoothSerial;
        vector<string> ssids;
        vector<string> passwords;
        vector<string> convertirDeCsvACredenciales(string csv);
};

#endif