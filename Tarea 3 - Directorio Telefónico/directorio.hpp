
#ifndef DIRECTORIO_HPP
#define DIRECTORIO_HPP

#include "error.hpp"
#include "directorio.hpp"
#include "list.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <memory>

using std::string;

namespace directorio{
    //structura para directorio
    struct EntradaDirectorio {
        string nombre;
        string telefono;
        string direccion;
        string email;
    };
    //lectura de archivo de directorio
    void cargarDirectorio(string archivo, LinkedList<EntradaDirectorio> &directorio);
    //escritura de archivo de directorio
    void escribirDirectorio(string archivo, LinkedList<EntradaDirectorio> &directorio);
    //Alta en directorio
    void altaDirectorio(string nombre, string telefono, string direccion, string email, LinkedList<EntradaDirectorio> &directorio);
    void altaDirectorio(EntradaDirectorio entrada, LinkedList<EntradaDirectorio> &directorio);
    //Baja en directorio
    directorio::EntradaDirectorio bajaDirectorio(string telefono, LinkedList<EntradaDirectorio> &directorio);
    //Modificar directorio
    void modificarDirectorio(EntradaDirectorio entradaNueva, EntradaDirectorio &entradaAntigua);
    //Listado de directorio
    void printEntradas(LinkedList<EntradaDirectorio> &entradas);
    void printEntrada(const EntradaDirectorio &entrada);
    //Consulta por nombre o numero de telefono
    LinkedList<EntradaDirectorio> encuentraNombre(string nombre, LinkedList<EntradaDirectorio> &directorio);
    LinkedList<EntradaDirectorio> encuentraTelefono(string telefono, LinkedList<EntradaDirectorio> &directorio);
}
#endif