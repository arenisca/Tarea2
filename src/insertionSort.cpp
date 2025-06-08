#include "../include/librerias.hpp"
#include "../include/interfaz_menu.hpp"
#include "../include/cargar_arreglo.hpp"

bool esta_ordenado(std::bitset<32>* arr, int n) {
    for (int i = 1; i < n; ++i) {
        if (arr[i - 1].to_ulong() > arr[i].to_ulong()) {
            return false;
        }
    }
    return true;
}

void insertion_sort(std::bitset<32>* arr, int n) {
    for (int i = 1; i < n; ++i) {
        std::bitset<32> clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].to_ulong() > clave.to_ulong()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
    }
}

int main() {
    OpcionesMenu opciones = mostrar_menu();
    int n;
    double tiempo_total = 0;
    std::vector<double> tiempos_individuales;

    std::ofstream out(opciones.ruta_csv);
    if (!out) {
        std::cerr << "No se pudo crear el archivo de salida.\n";
        return 1;
    }

    out << std::fixed << std::setprecision(7);
    out << "Algoritmo;InsertionSort\n";
    out << "Tamaño;" << opciones.tam << "\n";
    out << "Orden;" << opciones.ord << "\n"; 
    out << "Repeticiones;" << opciones.repeticiones << "\n";

    for (int i = 0; i < opciones.repeticiones; ++i) {
        std::bitset<32>* arreglo = cargar_arreglo(opciones.nombre_archivo, n);
        if (!arreglo) {
            std::cerr << "Error al cargar el arreglo.\n";
            return 1;
        }

        auto inicio = std::chrono::steady_clock::now();
        insertion_sort(arreglo, n);
        auto fin = std::chrono::steady_clock::now();

        double duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count() * 1e-9;
        tiempos_individuales.push_back(duracion);
        tiempo_total += duracion;

        if (!esta_ordenado(arreglo, n)) {
            std::cerr << "Error: El arreglo no quedó ordenado en la ejecución " << i + 1 << "\n";
        }

        delete[] arreglo;
    }

    double tiempo_promedio = tiempo_total / opciones.repeticiones;
    out << "Tiempo total;" << tiempo_total << "s\n";
    out << "Tiempo promedio;" << tiempo_promedio << "s\n";
    out << "Tiempos individuales (s):\n";
    for (size_t i = 0; i < tiempos_individuales.size(); ++i) {
        out << "Ejecución " << (i + 1) << ";" << tiempos_individuales[i] << "\n";
    }

    out.close();
    std::cout << "Resultados guardados en: " << opciones.ruta_csv << "\n";
    return 0;
}