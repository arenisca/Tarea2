#include "../include/librerias.hpp"
#include "../include/interfaz_menu.hpp"

void crear_csv_resultados(const std::string& ruta_csv, const OpcionesMenu& opciones, 
                         const std::vector<double>& tiempos_individuales, double tiempo_total) {
    std::ofstream out(ruta_csv);
    if (!out) {
        std::cerr << "No se pudo crear el archivo de salida.\n";
        return;
    }

    // Configuración del formato de salida
    out << std::fixed << std::setprecision(7);
    out << "Algoritmo;InsertionSort\n";
    out << "Tamaño;" << opciones.tam << "\n";
    out << "Orden;" << opciones.ord << "\n";
    out << "Repeticiones;" << opciones.repeticiones << "\n";
    out << "Máquina;" << opciones.maquina << "\n";

    double tiempo_promedio = tiempo_total / opciones.repeticiones;
    out << "Tiempo total;" << tiempo_total << "s\n";
    out << "Tiempo promedio;" << tiempo_promedio << "s\n";
    out << "Tiempos individuales (s):\n";
    for (size_t i = 0; i < tiempos_individuales.size(); ++i) {
        out << "Ejecución " << (i + 1) << ";" << tiempos_individuales[i] << "\n";
    }

    out.close();
}