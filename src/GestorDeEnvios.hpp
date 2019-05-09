#ifndef GESTORDEENVIOS_H
#define GESTORDEENVIOS_H
#include <HTTPClient.h>

class GestorDeEnvios{
    public:
        GestorDeEnvios();
        void enviar(String contenidoArchivo);
    private:
        HTTPClient cliente;
};

#endif