#ifndef GESTORDEENVIOS_H
#define GESTORDEENVIOS_H
#include <HTTPClient.h>

#define CANTIDAD_DE_INTENTOS_MAXIMA 10

class GestorDeEnvios{
    public:
        GestorDeEnvios();
        bool enviar(String contenidoArchivo);
        bool estaConectado();
        bool conectar();
    private:
        HTTPClient cliente;
};

#endif