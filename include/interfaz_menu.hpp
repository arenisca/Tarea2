#ifndef INTERFAZ_MENU_HPP
#define INTERFAZ_MENU_HPP

#include "librerias.hpp" 

struct OpcionesMenu {
    std::string nombre_archivo;
    std::string ruta_csv;
    int repeticiones;
    std::string tam;  // nuevo
    std::string ord;  // nuevo
};

OpcionesMenu mostrar_menu();

#endif
