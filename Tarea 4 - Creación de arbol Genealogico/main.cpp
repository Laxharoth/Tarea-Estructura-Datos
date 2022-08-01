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

    int insert[31]{
                          16,
              8,                        24,
         4,        12,            20,         28,
      2,   6,    10,  14,      18,  22,   26,   30,
    1,  3,5, 7,  9,11,13,15, 17,19,21,23,25,27,29, 31
              
        };
    string title[31]{
        "Hijo",
            "Mama","Papa",
                "Abuela materna", "Abuelo materno", "Abuela paterna", "Abuelo paterno",
                    "Bisabuela materna materna", "Bisabuelo materno materno", "Bisabuela materna paterna", "Bisabuelo materno paterno",
                    "Bisabuela paterna materna", "Bisabuelo paterno materno", "Bisabuela paterna paterna", "Bisabuelo paterno paterno",
                    "Tatara Abuela materna materna materna", "Tatara Abuelo materno materno materno", "Tatara Abuela materna materna paterna", "Tatara Abuelo materno materno paterno",
                    "Tatara Abuela materna paterna materna", "Tatara Abuelo materno paterno materno", "Tatara Abuela materna paterna paterna", "Tatara Abuelo materno paterno paterno",
                    "Tatara Abuela paterna materna materna", "Tatara Abuelo paterno materno materno", "Tatara Abuela paterna materna paterna", "Tatara Abuelo paterno materno paterno",
                    "Tatara Abuela paterna paterna materna", "Tatara Abuelo paterno paterno materno", "Tatara Abuela paterna paterna paterna", "Tatara Abuelo paterno paterno paterno",
    };
    Tree<IntegranteFamilia> tree;
    for (size_t i = 0; i < 31; i++){
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