#include "tree.hpp"
#include "arbol_genealogico.hpp"

#include <iostream>
#include <string>
#include <cstdio>

using std::cin;
using std::string;

const int WRONG_CHOICE_ERROR = 0b1;


void get_choice(int &choose, int min, int max);
void get_string(string &str);
void main_menu(Tree<IntegranteFamilia> &tree);
void enterPause();
void get_IntegranteFamilia(TreeNode<IntegranteFamilia> *node);

int main(){
    // int insert[15]{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    // int insert[15]{15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
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
    // tree.levelorder( [](TreeNode<IntegranteFamilia> *node){ std::cout << node->data.nombre << std::endl; }) ;
    main_menu(tree);
}
void get_choice(int &choose, int min, int max){
    cin >> choose;
    string rest;
    std::getline(cin, rest);
    if(choose < min || choose > max) throw WRONG_CHOICE_ERROR;
    system("cls");
}
void get_string(string &str){
    std::getline(cin, str);
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
    getchar();
    system("cls");
}