#ifndef MANEJADORDEARCHIVOS_H
#define MANEJADORDEARCHIVOS_H

class ManejadorDeArchivos{
    public:
        ManejadorDeArchivos();
        void escribir(String buffer[], int longitudBuffer);
        void listarArchivos();
        void disponibilizarParaTransferencia(String nombreDestino);
        String obtenerContenido(String nombreArchivo);
    private:
        void reiniciarArchivoDeDatos();
};

#endif