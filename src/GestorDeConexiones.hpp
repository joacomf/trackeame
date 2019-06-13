#ifndef GESTORDECONEXIONES_H
#define GESTORDECONEXIONES_H

#include "Credencial.hpp"

using namespace std;

class GestorDeConexiones {
    public:
        GestorDeConexiones(vector<Credencial*> credenciales);
        void conectar();
        bool estaConectado();
    private:
        const int CANTIDAD_DE_INTENTOS_MAXIMA = 10;
        vector<Credencial*> credenciales;
        void buscarRedesYConectar();
        int obtenerCantidadDeRedesDisponibles();
        vector<string> obtenerRedesDisponibles();
        void intentarConectarARedesDisponibles(vector<string> redesDisponibles);
};

#endif