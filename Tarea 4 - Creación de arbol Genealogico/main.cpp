#include "tree.hpp"
#include "arbol_genealogico.hpp"

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
void get_string(string &str);
void main_menu(Tree<IntegranteFamilia> &tree);
void enterPause();
void get_IntegranteFamilia(TreeNode<IntegranteFamilia> *node);

int main(int argc, char* argv[]){
    std::unique_ptr<std::ifstream> file;
    if(argc > 1){
        const char* filename =  argv[1];
        file = std::make_unique<std::ifstream>(filename);
        if(file->is_open())
            STREAM = file.get();
    }

    int insert[15]{
        8,
        4,12,
        2,6,10,14,
        1,3,5,7,
        9,11,13,15};
    string title[15]{
        "Hijo",
        "Mama","Papa",
        "Abuela materna", "Abuelo materno", "Abuela paterno", "Abuelo paterno",
            "Tatara Abuela materna materna", "Tatara Abuelo materno materna", "Tatara Abuela materna paterno", "Tatara Abuelo materno paterno",
            "Tatara Abuela paterno materna", "Tatara Abuelo paterno materna", "Tatara Abuela paterno paterno", "Tatara Abuelo paterno paterno",
    };
    Tree<IntegranteFamilia> tree;
    for (size_t i = 0; i < 15; i++){
        tree.insert(IntegranteFamilia{insert[i],title[i]});
    }
    main_menu(tree);
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
void get_string(string &str){
    std::getline(*STREAM, str);
    set_STREAM();
}
void main_menu(Tree<IntegranteFamilia> &tree){
    int opcion;
    system("cls");
    while(true){
        printf("Seleccione la opcion que desea\n");
        printf("1.- Inicializar arbol\n");
        printf("2.- Mostrar la informacion de todos los parientes de sexo masculino\n");
        printf("3.- Mostrar los nombres de los tatarabuelos\n");
        printf("0.- Salir\n");
        printf("\nseleccion:");
        get_choice(opcion, 0, 3);
        switch(opcion){
            case 1:
            tree.levelorder(get_IntegranteFamilia);
            break;
            case 2:
            printMasculino(tree); 
            enterPause();
            break;
            case 3:
            printTararabuelo(tree);
            enterPause();
            break;
            case 0:return;
        }
    }
}

void get_IntegranteFamilia(TreeNode<IntegranteFamilia> *nodo){
    IntegranteFamilia &familiar = nodo->data;
    printf("Ingrese la informacion (%s)",familiar.nombre.c_str());
    printf("Nombre:");
    get_string(familiar.nombre);
    printf("Fecha de Nacimiento:");
    get_string(familiar.fechaNacimiento);
    printf("Lugar de Nacimiento:");
    get_string(familiar.lugarNacimiento);
    enterPause();
}
void enterPause(){
    printf("\nPresina [Enter] para continuar:");
    if( STREAM ==  &cin) getchar();
    system("cls");
}