#ifndef GESTORDEENVIOS_H
#define GESTORDEENVIOS_H
#include <HTTPClient.h>

class GestorDeEnvios{
    public:
        GestorDeEnvios();
        bool enviar(String contenidoArchivo);
        bool estaConectado();
    private:
        HTTPClient cliente;
};

#endif