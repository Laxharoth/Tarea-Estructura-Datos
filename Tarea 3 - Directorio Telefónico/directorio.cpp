#include "directorio.hpp"

namespace directorio {
    void cargarDirectorio(string archivo, LinkedList<EntradaDirectorio> &directorio){
        auto file = std::ifstream(archivo,std::ifstream::binary);
        if(!file.is_open()) return;
        EntradaDirectorio entrada{};
        // guarda la cantidad de numeros registrados
        size_t tamanoDirectorio;
        file.read((char*) &tamanoDirectorio,sizeof tamanoDirectorio);
        auto readField =  [&file](string &field){
            size_t size{};
            file.read((char*) &size,sizeof size);
            auto value = std::unique_ptr<char[]>( new char[size+1]);
            value[size] = 0;
            file.read(value.get(),size);
            field = string(value.get());
        };
        for (size_t i = 0; i < tamanoDirectorio; i++){
            readField(entrada.nombre);
            readField(entrada.telefono);
            readField(entrada.direccion);
            readField(entrada.email);
            directorio.insert(entrada);
        }
        file.close();
    }
    void escribirDirectorio(string archivo, LinkedList<EntradaDirectorio> &directorio){
        string tempName = archivo+".temp";
        auto file = std::ofstream(tempName,std::ifstream::binary);
        auto writeIntoFile = [&file](const string &field){
            size_t size{};
            size = field.length();
            file.write((char*) &size,sizeof size);
            file.write(field.c_str(), size);
        };
        size_t tamanoDirectorio = directorio.size;
        file.write((char*) &(tamanoDirectorio),sizeof tamanoDirectorio);
        auto node = directorio.begin();
        while(node != directorio.end()){
            writeIntoFile((*node).nombre);
            writeIntoFile((*node).telefono);
            writeIntoFile((*node).direccion);
            writeIntoFile((*node).email);
            node = node.next();
        }
        file.close();
        std::remove(archivo.c_str());
        std::rename(tempName.c_str(), archivo.c_str());
    }
    void altaDirectorio(string nombre, string telefono, string direccion, string email, LinkedList<EntradaDirectorio> &directorio){
        EntradaDirectorio entrada{nombre, telefono, direccion, email};
        altaDirectorio(entrada, directorio);
    }
    void altaDirectorio(EntradaDirectorio entrada, LinkedList<EntradaDirectorio> &directorio){
        if(encuentraTelefono(entrada.telefono,directorio).size!=0) throw INGRESAR_TELEFONO_EXISTENTE_ERROR;
        directorio.insert(entrada);
    }
    EntradaDirectorio bajaDirectorio(string telefono, LinkedList<EntradaDirectorio> &directorio){
        auto recorre = directorio.begin();
        while(recorre != directorio.end() && (*recorre).telefono != telefono) recorre = recorre.next();
        if(recorre == directorio.end()) throw ELIMINAR_TELEFONO_NO_EXISTENTE_ERROR;
        EntradaDirectorio eliminar = directorio.remove(recorre);
        return eliminar;
    }
    LinkedList<EntradaDirectorio> encuentraNombre(string nombre, LinkedList<EntradaDirectorio> &directorio){
        LinkedList<EntradaDirectorio> coincidencias{};
        auto recorre = directorio.begin();
        while(recorre != directorio.end()){
            if(nombre == (*recorre).nombre){
                coincidencias.insert(*recorre);
            }
            recorre = recorre.next();
        }
        return coincidencias;
    }
    LinkedList<EntradaDirectorio> encuentraTelefono(string telefono, LinkedList<EntradaDirectorio> &directorio){
        LinkedList<EntradaDirectorio> coincidencias{};
        auto recorre = directorio.begin();
        while(recorre != directorio.end()){
            auto entrada = *recorre;
            recorre = recorre.next();
            // solo debería haber una entrada por numero de telefono
            if(entrada.telefono != telefono) continue;
            coincidencias.insert(entrada);
            return coincidencias;
        }
        return coincidencias;
    }
    void printEntradas(LinkedList<EntradaDirectorio> &entradas){
        auto recorre = entradas.begin();
        while(recorre != entradas.end()){
            printEntrada(*recorre);
            recorre = recorre.next();
        }
    }
    void printEntrada(const EntradaDirectorio &entrada){
        string entradaStr = "*--------------------------------------\n";
        entradaStr += "* nombre:    %s\n";
        entradaStr += "* telefono:  %s\n";
        entradaStr += "* direccion: %s\n";
        entradaStr += "* correo:    %s\n";
        entradaStr += "*\t\n";
        printf(entradaStr.c_str(), entrada.nombre.c_str(), entrada.telefono.c_str(), entrada.direccion.c_str(), entrada.email.c_str());
    }
    void modificarDirectorio(EntradaDirectorio entradaNueva, EntradaDirectorio &entradaAntigua){
        entradaAntigua.nombre = entradaNueva.nombre;
        entradaAntigua.telefono = entradaNueva.telefono;
        entradaAntigua.direccion= entradaNueva.direccion;
        entradaAntigua.direccion = entradaNueva.direccion;       
    }
}