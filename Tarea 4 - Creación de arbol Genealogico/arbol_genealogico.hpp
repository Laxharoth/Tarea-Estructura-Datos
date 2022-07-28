#ifndef ARBOL_GEN_HPP
#define ARBOL_GEN_HPP

#include "tree.hpp"

#include <cstdio>
#include <string>

using std::string;

struct IntegranteFamilia{
    int id;
    string nombre{};
    string fechaNacimiento{};
    string lugarNacimiento{};
    bool operator==(IntegranteFamilia const& rhs);
    bool operator!=(IntegranteFamilia const& rhs);
    bool operator>=(IntegranteFamilia const& rhs);
    bool operator<=(IntegranteFamilia const& rhs);
    bool operator>( IntegranteFamilia const& rhs);
    bool operator<( IntegranteFamilia const& rhs);
};

void printIntegranteFamilia(const IntegranteFamilia& rhs);
void printMasculino(Tree<IntegranteFamilia> &tree);
void printTararabuelo(Tree<IntegranteFamilia> &tree);
#endif