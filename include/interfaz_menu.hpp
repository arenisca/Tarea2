#ifndef INTERFAZ_MENU_HPP
#define INTERFAZ_MENU_HPP

#include "librerias.hpp" 

struct OpcionesMenu {
    std::string nombre_archivo;
    std::string ruta_csv;
    int repeticiones;
    std::string tam;
    std::string ord;
    std::string maquina;
    std::string algoritmo;
};

OpcionesMenu mostrar_menu(const std::string& algoritmo);

#endif