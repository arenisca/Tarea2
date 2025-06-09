#include "../include/interfaz_menu.hpp"

OpcionesMenu mostrar_menu(const std::string& nombre_algoritmo) {
    std::string carpeta = "../archivos_de_prueba";
    std::vector<std::string> tamanos = {"5000", "50000", "500000"};
    std::vector<std::string> ordenes = {"asc", "desc", "shuffled"};
    std::vector<std::string> maquinas = {
        "Maquina 1 (Lucas)",
        "Maquina 2 (Vale)"
    };

    int opcion_tam, opcion_ord, opcion_maquina, repeticiones;

    // Selección de máquina
    std::cout << "Seleccione la maquina:\n";
    for (size_t i = 0; i < maquinas.size(); ++i) {
        std::cout << i + 1 << ". " << maquinas[i] << "\n";
    }
    std::cin >> opcion_maquina;

    // Resto del menú (tamaño, orden, repeticiones)
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

    std::cout << "Ingrese el numero de ejecuciones (maximo 10000): ";
    std::cin >> repeticiones;

    if (repeticiones > 10000) {
        std::cout << "Se ha alcanzado el máximo permitido (10000 ejecuciones).\n";
        repeticiones = 10000;
    } else if (repeticiones <= 0) {
        std::cout << "El número de ejecuciones debe ser mayor que 0. Usando 1 por defecto.\n";
        repeticiones = 1;
    }

    // Configurar opciones
    OpcionesMenu opciones;
    opciones.maquina = (opcion_maquina == 1) ? "Lucas" : "Vale"; // Guardamos solo el nombre
    opciones.nombre_archivo = carpeta + "/lcp_" + tamanos[opcion_tam - 1] + "_" + ordenes[opcion_ord - 1] + ".bin";
    opciones.ruta_csv = "../Resultados_CSV/" + opciones.maquina + "/" +
                    nombre_algoritmo + "_" + tamanos[opcion_tam - 1] + "_" +
                    ordenes[opcion_ord - 1] + "_" + std::to_string(repeticiones) + ".csv";
    opciones.repeticiones = repeticiones;
    opciones.tam = tamanos[opcion_tam - 1];
    opciones.ord = ordenes[opcion_ord - 1];
    

    return opciones;
}
