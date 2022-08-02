#include "b-tree.hpp"
#include "PaquetePedido.hpp"

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <memory>

using std::cin;
using std::string;

const int WRONG_CHOICE_ERROR = 0b1;

static std::istream *STREAM = &cin;
void get_choice(int &choose, int min, int max);
void get_int(int  &i);
void get_string(string &str);
void main_menu(BTree<PaquetePedido> &tree);
void enterPause();
void get_PaquetePedido(PaquetePedido &pedido);
void insertPaquete(BTree<PaquetePedido> &tree);
void searchPaquete(BTree<PaquetePedido> &tree);
void printPack(const PaquetePedido &pack);


int main(int argc, char* argv[]){
    std::unique_ptr<std::ifstream> file;
    if(argc > 1){
        const char* filename =  argv[1];
        file = std::make_unique<std::ifstream>(filename);
        if(file->is_open())
            STREAM = file.get();
    }

    BTree<PaquetePedido> tree;
    main_menu(tree);
    return 0; 
}
void set_STREAM(){
    if( STREAM != &cin && STREAM->peek() == EOF){
        STREAM = &cin;
    }
}
void get_choice(int &choose, int min, int max){
    *STREAM >> choose;
    string rest;
    std::getline(*STREAM, rest);
    set_STREAM();
    if(choose < min || choose > max) throw WRONG_CHOICE_ERROR;
    system("cls");
}
void get_int(int &i){
    string str;
    std::getline(*STREAM, str);
    i = std::stoi(str);
    set_STREAM();
}
void get_string(string &str){
    std::getline(*STREAM, str);
    set_STREAM();
}
void main_menu(BTree<PaquetePedido> &tree){
    int opcion;
    system("cls");
    while(true){
        printf("Seleccione la opcion que desea\n");
        printf("1.- Envio de paquete:\n");
        printf("2.- Rastreo de pedidos.\n");
        printf("0.- Salir\n");
        printf("\nseleccion:");
        get_choice(opcion, 0, 3);
        switch(opcion){
            case 1:
            insertPaquete(tree);
            break;
            case 2:
            searchPaquete(tree);
            break;
            case 3:
            break;
            case 0:return;
        }
    }
}

void get_PaquetePedido(PaquetePedido &pedido){
    printf("Ingrese la informacion:\n");
    printf("Nombre Remitente: ");
    get_string(pedido.nombre_remitente);
    printf("Nombre Destinatario: ");
    get_string(pedido.nombre_destinatario);
    printf("Estado Envio: ");
    get_string(pedido.estado_envio);
    printf("Destino Direccion: ");
    get_string(pedido.destino_direccion);
}
void enterPause(){
    printf("\nPresina [Enter] para continuar:");
    if( STREAM ==  &cin) getchar();
    system("cls");
}
void insertPaquete(BTree<PaquetePedido> &tree){
    PaquetePedido pack(true);
    get_PaquetePedido(pack);
    tree.insert(pack);
    // asegurarse que el contador este correcto
    next_numero_pedido = pack.numero_pedido;
    printPack(pack);
    enterPause();
}
void searchPaquete(BTree<PaquetePedido> &tree){
    printf("Ingrese el Numero de Pedido:");
    int id;get_int(id);
    PaquetePedido searchPack((long long) id);
    try{
        const PaquetePedido &pack = tree.find(searchPack);
        printPack(pack);
    }
    catch(int error){
        if(error != B_TREE_ERROR_NOT_FOUND){
            throw error;
        }
        printf("Paquete con id \"%s\" no fue encontrado.\n", id);
    }
    enterPause();
}
void printPack(const PaquetePedido &pack){
    printf("********************************\n");
    printf("* Numero de pedido: %d\n",pack.numero_pedido);
    printf("* Nombre Reminente: %s\n",pack.nombre_remitente.c_str());
    printf("* Nombre Destinatario: %s\n",pack.nombre_destinatario.c_str());
    printf("* Status: %s\n",pack.estado_envio.c_str());
    printf("* Direccion Destino: %s\n",pack.destino_direccion.c_str());
    printf("*******\n");
}