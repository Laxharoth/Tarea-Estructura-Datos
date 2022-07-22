#include "directorio.hpp"
#include "error.hpp"
#include "list.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

const string NOMBRE_ARCHIVO_DIRECTORIO = "telefonos.tel";

using std::cout;
using std::cin;
using std::endl;
using std::string;
using directorio::EntradaDirectorio;

void solicitaEntradaDirectorio(LinkedList<EntradaDirectorio> &myDirectorio);
void solicitaTelefonoParaEliminar(LinkedList<EntradaDirectorio> &myDirectorio);
void solicitaTelefonoParaModificar(LinkedList<EntradaDirectorio> &myDirectorio);
void menuBusqueda(LinkedList<EntradaDirectorio> &myDirectorio);
void menuModificarEntrada(directorio::EntradaDirectorio &entradaAntigua);
void enterPause();
void printError(int error_code);
void cancelarAccionMsg();
int mainMenu();

int main(){
    system("cls");
    LinkedList<EntradaDirectorio> myDirectorio{};
    directorio::cargarDirectorio(NOMBRE_ARCHIVO_DIRECTORIO, myDirectorio);
    int choose{0};
    do{
        try{
            choose = mainMenu();
            switch(choose){
                //1.- Alta de suscriptores.
                case 1: solicitaEntradaDirectorio(myDirectorio);break;
                //2.- Baja de suscriptores.
                case 2: solicitaTelefonoParaEliminar(myDirectorio);break;
                //3.- Modificación de datos.
                case 3: solicitaTelefonoParaModificar(myDirectorio);break;
                //4.- Listado de todos los suscriptores.
                case 4: directorio::printEntradas(myDirectorio);
                printf("end print");
                enterPause();
                break;
                //5.- Consulta de suscriptores.
                case 5: menuBusqueda(myDirectorio);break;
            }
        }catch(int error_code){
            printError(error_code);
            choose = -1;
        }
    }
    while(choose != 0);
    directorio::escribirDirectorio(NOMBRE_ARCHIVO_DIRECTORIO, myDirectorio);
}

void solicitaEntradaDirectorio(LinkedList<EntradaDirectorio>& myDirectorio){
    directorio::EntradaDirectorio entrada{};
    cout << "Ingrese los datos para el directorio";
    cout << endl << "Telefono:\t";
    std::getline(cin,entrada.telefono);
    // si el telefono ya existe no se molesta en preguntar por los otros datos
    if( directorio::encuentraTelefono(entrada.telefono,myDirectorio).size  ){
        throw INGRESAR_TELEFONO_EXISTENTE_ERROR;
    }
    cout << "Nombre:\t";
    std::getline(cin,entrada.nombre);
    cout << "Direccion:\t";
    std::getline(cin,entrada.direccion);
    cout << "Email:\t";
    std::getline(cin,entrada.email);
    directorio::altaDirectorio(entrada,myDirectorio);
    system("cls");
    directorio::printEntrada(entrada);
    enterPause();
}
void solicitaTelefonoParaEliminar(LinkedList<EntradaDirectorio>& myDirectorio){
    string telefono{};
    cout << "Ingrese el telefono para eliminar: ";
    std::getline(cin,telefono);
    system("cls");
    directorio::EntradaDirectorio entradaEliminada = directorio::bajaDirectorio(telefono, myDirectorio);
    cout << "Contacto Eliminado" << endl;
    directorio::printEntrada(entradaEliminada);
    enterPause();
}
void solicitaTelefonoParaModificar(LinkedList<EntradaDirectorio> &myDirectorio){
    string telefono{};
    cout << "Ingrese el telefono para eliminar: ";
    std::getline(cin , telefono);
    system("cls");
    auto recorre = myDirectorio.begin();
    while(recorre != myDirectorio.end() && (*recorre).telefono != telefono) recorre = recorre.next();
    if(recorre == myDirectorio.end()) throw ACTUALIZAR_TELEFONO_INEXISTENTE_ERROR;
    menuModificarEntrada(*recorre);
}
void enterPause(){
    cout << endl << "Presina [Enter] para continuar:";
    getchar();
    system("cls");
}
int mainMenu(){
    int opcion;
    cout << "Seleccionar la opcion." << endl;
    cout << "1.- Alta de suscriptores." << endl;
    cout << "2.- Baja de suscriptores." << endl;
    cout << "3.- Modificaci\xA2n de datos." << endl;
    cout << "4.- Listado de todos los suscriptores." << endl;
    cout << "5.- Consulta de suscriptores." << endl;
    cout << "0.- Salir." << endl;
    cout << endl << "Opcion: "; 
    cin>>opcion;
    string restOfLine;
    std::getline(cin, restOfLine);
    system("cls");
    if(opcion < 0 || opcion > 5){
        throw OPCION_INVALIDA_ERROR;
    }
    return opcion;
}
void menuBusqueda(LinkedList<EntradaDirectorio> &myDirectorio){
    int opcion = 0;
    cout << "Seleccionar la opcion." << endl;
    cout << "1.- Busqueda por Nombre." << endl;
    cout << "2.- Busqueda por Telefono." << endl;
    cin >> opcion;
    string restLine;
    std::getline(cin, restLine);
    system("cls");
    if( opcion != 1 && opcion != 2 ) throw OPCION_INVALIDA_ERROR;
    string busquedaStr;
    string NombreCampo;
    if(opcion == 1) NombreCampo = "Nombre";
    else NombreCampo = "Telefono";
    cout << "Ingresar " << NombreCampo << ":";
    std::getline(cin, busquedaStr);
    system("cls");
    
    if(opcion == 1){
        auto entradas = directorio::encuentraNombre(busquedaStr,myDirectorio);
        directorio::printEntradas(entradas);
    }     
    else {
        auto entradas = directorio::encuentraTelefono(busquedaStr,myDirectorio);
        directorio::printEntradas(entradas);
    }
    enterPause();
}
void menuModificarEntrada(directorio::EntradaDirectorio &entradaAntigua){
    directorio::EntradaDirectorio entradaCopia = entradaAntigua;
    int opcion = 0;
    do{
        system("cls");
        cout << "Informacion del numero a modificar." << endl;
        directorio::printEntrada(entradaCopia);

        string *campoCambiar = nullptr;
        string nombreCampo{};

        cout << "Seleccionar el campo que desea modificar." << endl;
        cout << "1.- Nombre." << endl;
        cout << "2.- Telefono." << endl;
        cout << "3.- Direccion." << endl;
        cout << "4.- Correo." << endl;
        cout << endl << "5.- Guardar." << endl;
        cout << "0.- Cancelar." << endl;
        cout << "opcion: ";
        cin >> opcion;
        string restLine;
        std::getline(cin, restLine);
        system("cls");
        try{
            switch (opcion){
            case 1: nombreCampo = "Nombre";    campoCambiar = &(entradaCopia.nombre);break;
            case 2: nombreCampo = "Telefono";  campoCambiar = &(entradaCopia.telefono);break;
            case 3: nombreCampo = "Direccion"; campoCambiar = &(entradaCopia.direccion);break;
            case 4: nombreCampo = "Correo";    campoCambiar = &(entradaCopia.email);break;
            case 5: 
                directorio::modificarDirectorio(entradaCopia, entradaAntigua);
                return;
            case 0: 
                cancelarAccionMsg();
                return;
            default: throw OPCION_INVALIDA_ERROR;
            }
            cout << "Modificar " << nombreCampo << ":";
            std::getline(cin,*campoCambiar);
            system("cls");
        }catch(int error_code){
            printError(error_code);
        }
    }while(opcion != 5);
}
void printError(int error_code){
    switch(error_code){
        case INGRESAR_TELEFONO_EXISTENTE_ERROR:
            cout << "El telefono que se intenta ingresar ya existe" << endl;
            break;
        case ELIMINAR_TELEFONO_NO_EXISTENTE_ERROR:
            cout << "El telefono que se intenta eliminar no existe" << endl;
            break;
        case ACTUALIZAR_TELEFONO_INEXISTENTE_ERROR:
            cout << "El telefono que se intenta actializar no existe" << endl;
            break;
        case OPCION_INVALIDA_ERROR:
            cout << "La opcion seleccionada no es valida" << endl;
            break;
    }
    enterPause();
}
void cancelarAccionMsg(){
    system("cls");
    cout << "Accion Cancelada"<< endl;
    enterPause();
}
