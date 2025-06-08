#include "../include/interfaz_menu.hpp"
#include <iostream>

OpcionesMenu mostrar_menu() {
    std::string carpeta = "../archivos_de_prueba";
    std::vector<std::string> tamanos = {"5000", "50000", "500000"};
    std::vector<std::string> ordenes = {"asc", "desc", "shuffled"};

    int opcion_tam, opcion_ord, repeticiones;

    std::cout << "Seleccione el tamano del archivo:\n";
    for (size_t i = 0; i < tamanos.size(); ++i) {
        std::cout << i + 1 << ". " << tamanos[i] << "\n";
    }
    std::cin >> opcion_tam;

    std::cout << "Seleccione el orden del archivo:\n";
    for (size_t i = 0; i < ordenes.size(); ++i) {
        std::cout << i + 1 << ". " << ordenes[i] << "\n";
    }
    std::cin >> opcion_ord;

    std::cout << "Ingrese el numero de ejecuciones: ";
    std::cin >> repeticiones;

    std::string tam = tamanos[opcion_tam - 1];
    std::string ord = ordenes[opcion_ord - 1];

    OpcionesMenu opciones;
    opciones.nombre_archivo = carpeta + "/lcp_" + tam + "_" + ord + ".bin";
    opciones.ruta_csv = "../Resultados_CSV/" + tam + "_" + ord + "_" + std::to_string(repeticiones) + ".csv";
    opciones.repeticiones = repeticiones;
    opciones.tam = tam;  // nuevo campo
    opciones.ord = ord;  // nuevo campo

    return opciones;
}
