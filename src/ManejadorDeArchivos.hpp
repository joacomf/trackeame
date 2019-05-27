#ifndef MANEJADORDEARCHIVOS_H
#define MANEJADORDEARCHIVOS_H

#include <bits/stdc++.h>
using namespace std;

class ManejadorDeArchivos{
    public:
        ManejadorDeArchivos();
        void escribir(vector<string> posiciones);
        void disponibilizarParaTransferencia(String nombreDestino);
        String obtenerContenido(String nombreArchivo);
        string obtenerProximoArchivoParaEnviar();
    private:
        void reiniciarArchivoDeDatos();
};

#endif