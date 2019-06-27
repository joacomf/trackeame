#ifndef GESTORDECONEXIONES_H
#define GESTORDECONEXIONES_H

#include "Credencial.hpp"

using namespace std;

class GestorDeConexiones {
    public:
        GestorDeConexiones(vector<Credencial*> credenciales);
        void buscarRedesYConectar();
        bool estaConectado();
        void desconectar();
    private:
        const int CANTIDAD_DE_INTENTOS_MAXIMA = 10;
        vector<Credencial*> credenciales;
        int obtenerCantidadDeRedesDisponibles();
        vector<string> obtenerRedesDisponibles();
        void intentarConectarConCredencialesGuardadas(vector<string> redesDisponibles);
        void conectarConRed(string redGuardada, string password);
        void intentarConectarConRedesDisponibles(vector<string> redesDisponibles, Credencial* credencial);
};

#endif