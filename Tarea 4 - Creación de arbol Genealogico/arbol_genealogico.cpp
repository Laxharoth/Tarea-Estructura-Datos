#include "arbol_genealogico.hpp"

bool IntegranteFamilia::operator==(IntegranteFamilia const& rhs){ return (*this).id == rhs.id;}
bool IntegranteFamilia::operator!=(IntegranteFamilia const& rhs){ return (*this).id != rhs.id;}
bool IntegranteFamilia::operator>=(IntegranteFamilia const& rhs){ return (*this).id >= rhs.id;}
bool IntegranteFamilia::operator<=(IntegranteFamilia const& rhs){ return (*this).id <= rhs.id;}
bool IntegranteFamilia::operator>( IntegranteFamilia const& rhs){ return (*this).id > rhs.id; }
bool IntegranteFamilia::operator<( IntegranteFamilia const& rhs){ return (*this).id < rhs.id; }

void soloDerecha( void (*callback)(TreeNode<IntegranteFamilia> *node) , TreeNode<IntegranteFamilia> *curr){
    if(curr == nullptr) return;
    if(curr->right != nullptr)
        callback(curr->right);
    soloDerecha(callback, curr->right);
    soloDerecha(callback, curr->left);
}
void printMasculino(Tree<IntegranteFamilia> &tree){
    soloDerecha([](TreeNode<IntegranteFamilia> *node){ 
        printIntegranteFamilia(node->data);
     }, tree.root);
}
void printTararabuelo(Tree<IntegranteFamilia> &tree){
    tree.levelorder([](TreeNode<IntegranteFamilia> *node){
        if(node->left == nullptr && node->right == nullptr){
            printIntegranteFamilia(node->data);
        }
    });
}
void printIntegranteFamilia(const IntegranteFamilia& integrante){
    printf("************************\n");
    printf("* Nombre : %s\n", integrante.nombre.c_str());
    printf("* Fecha Nacimiento: %s\n", integrante.fechaNacimiento.c_str());
    printf("* Lugar Nacimiento: %s\n", integrante.lugarNacimiento.c_str());
    printf("* * *\n");
}
