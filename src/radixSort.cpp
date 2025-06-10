#include "../include/librerias.hpp"
#include "../include/interfaz_menu.hpp"
#include "../include/cargar_arreglo.hpp"
#include "../include/creador_csv.hpp"

/*
Comandos para compilar:
g++ -I../include radixSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o radixSort
c++ -I../include radixSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o radixSort
cpp -I../include radixSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o radixSort
Comando para ejecutar:
.\radixSort.exe
*/

/**
 * @brief Radix Sort optimizado para enteros de 32 bits. Usa base 256 (1 byte) para mejorar el rendimiento.
 */
void radixSort(std::bitset<32>* arreglo, int n) {
    if (n <= 1) return;

    const int base = 256; // 2^8
    const int passes = 4; // 32 bits / 8 bits = 4 pases
    std::vector<std::bitset<32>> output(n);
    std::vector<int> count(base);

    for (int pass = 0; pass < passes; ++pass) {
        std::fill(count.begin(), count.end(), 0);

        int shift = pass * 8;

        // Contar ocurrencias
        for (int i = 0; i < n; ++i) {
            int digit = (arreglo[i].to_ulong() >> shift) & 0xFF;
            count[digit]++;
        }

        // Convertir a posiciones acumuladas
        for (int i = 1; i < base; ++i) {
            count[i] += count[i - 1];
        }

        // Ordenar de acuerdo al byte actual
        for (int i = n - 1; i >= 0; --i) {
            int digit = (arreglo[i].to_ulong() >> shift) & 0xFF;
            output[--count[digit]] = arreglo[i];
        }

        // Copiar de vuelta
        for (int i = 0; i < n; ++i) {
            arreglo[i] = output[i];
        }
    }
}

/**
 * @brief Verifica si un arreglo está ordenado ascendentemente.
 */
bool esta_ordenado(std::bitset<32>* arr, int n) {
    for (int i = 1; i < n; ++i) {
        if (arr[i - 1].to_ulong() > arr[i].to_ulong()) {
            return false;
        }
    }
    return true;
}

int main() {
    OpcionesMenu opciones = mostrar_menu("Radix_Sort");
    int n;
    double tiempo_total = 0;
    std::vector<double> tiempos_individuales;

    for (int i = 0; i < opciones.repeticiones; ++i) {
        std::bitset<32>* arreglo = cargar_arreglo(opciones.nombre_archivo, n);
        if (!arreglo || n <= 0) {
            std::cerr << "Error al cargar el arreglo.\n";
            return 1;
        }

        auto inicio = std::chrono::high_resolution_clock::now();
        radixSort(arreglo, n);
        auto fin = std::chrono::high_resolution_clock::now();

        double duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count() * 1e-9;

        if (duracion == 0.0) {
            std::cerr << "Tiempo cero en ejecucion " << i + 1 << ", repitiendo...\n";
            delete[] arreglo;
            --i;
            continue;
        }

        tiempos_individuales.push_back(duracion);
        tiempo_total += duracion;

        if (!esta_ordenado(arreglo, n)) {
            std::cerr << "Error: El arreglo no quedó ordenado en la ejecución " << i + 1 << "\n";
            delete[] arreglo;
            --i;
            continue;
        }

        delete[] arreglo;
    }

    crear_csv_resultados(opciones.ruta_csv, opciones, tiempos_individuales, tiempo_total, "Radix_Sort");

    std::cout << "Ordenamiento completado con exito.\n";
    std::cout << "Resultados guardados en: " << opciones.ruta_csv << "\n";

    return 0;
}
