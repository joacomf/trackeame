#ifndef GESTORDECONEXIONES_H
#define GESTORDECONEXIONES_H

#include "Credencial.hpp"

using namespace std;

class GestorDeConexiones {
    public:
        GestorDeConexiones();
        void conectar(vector<Credencial*> credenciales);
};

#endif