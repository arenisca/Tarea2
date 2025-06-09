#include "../include/interfaz_menu.hpp"

void crear_csv_resultados(
    const std::string& ruta_csv,
    const OpcionesMenu& opciones,
    const std::vector<double>& tiempos_individuales,
    double tiempo_total,
    const std::string& nombre_algoritmo)
{
    std::ofstream archivo(ruta_csv);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo CSV para escritura: " << ruta_csv << "\n";
        return;
    }

    // Calcular tiempo promedio
    double tiempo_promedio = tiempos_individuales.empty() ? 0.0 : tiempo_total / tiempos_individuales.size();

    archivo << "Algoritmo;" << nombre_algoritmo << "\n";
    archivo << "Tamaño;" << opciones.tam << "\n";
    archivo << "Orden;" << opciones.ord << "\n";
    archivo << "Repeticiones;" << opciones.repeticiones << "\n";
    archivo << "Máquina;" << opciones.maquina << "\n";
    archivo << "Tiempo total;" << tiempo_total << "s\n";
    archivo << "Tiempo promedio;" << tiempo_promedio << "s\n";
    archivo << "Tiempos individuales (s):\n";

    for (size_t i = 0; i < tiempos_individuales.size(); ++i) {
        archivo << "Ejecución " << (i + 1) << ";" << tiempos_individuales[i] << "\n";
    }

    archivo.close();
}
