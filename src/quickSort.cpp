#include "../include/librerias.hpp"
#include "../include/interfaz_menu.hpp"
#include "../include/cargar_arreglo.hpp"
#include "../include/creador_csv.hpp"

/*
Comandos para compilar:
g++ -I../include quickSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o quickSort
c++ -I../include quickSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o quickSort
cpp -I../include quickSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o quickSort
comando para ejecutar:
.\quickSort.exe
*/

/**
 * @brief Función para particionar el arreglo usando el pivote.
 * 
 * @param arr Arreglo de bitsets.
 * @param inicio Índice inicial del subarreglo.
 * @param fin Índice final del subarreglo.
 * @return int Índice donde quedó ubicado el pivote.
 */
int particionar(std::bitset<32>* arr, int inicio, int fin) {
    unsigned long pivote = arr[fin].to_ulong();
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (arr[j].to_ulong() <= pivote) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[fin]);
    return i + 1;
}

/**
 * @brief Implementación recursiva de QuickSort.
 * 
 * @param arr Arreglo de bitsets a ordenar.
 * @param inicio Índice inicial del subarreglo.
 * @param fin Índice final del subarreglo.
 */
void quickSort(std::bitset<32>* arr, int inicio, int fin) {
    if (inicio < fin) {
        int pivote = particionar(arr, inicio, fin);

        quickSort(arr, inicio, pivote - 1);
        quickSort(arr, pivote + 1, fin);
    }
}

/**
 * @brief Verifica si un arreglo está ordenado ascendentemente.
 * 
 * @param arr Arreglo de bitsets.
 * @param n Tamaño del arreglo.
 * @return true si está ordenado, false si no.
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
    OpcionesMenu opciones = mostrar_menu("Quick_Sort");
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
        quickSort(arreglo, 0, n - 1);
        auto fin = std::chrono::high_resolution_clock::now();

        double duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count() * 1e-9;
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

    crear_csv_resultados(opciones.ruta_csv, opciones, tiempos_individuales, tiempo_total, "Quick_Sort");

    std::cout << "Ordenamiento completado con exito.\n";
    std::cout << "Resultados guardados en: " << opciones.ruta_csv << "\n";

    return 0;
}
