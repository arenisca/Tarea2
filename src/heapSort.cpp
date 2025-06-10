#include "../include/librerias.hpp"
#include "../include/priorityQueue.hpp"
#include "../include/interfaz_menu.hpp"
#include "../include/cargar_arreglo.hpp"
#include "../include/creador_csv.hpp"

/*
Comandos para compilar:
g++ -I../include heapSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o heapSort
c++ -I../include heapSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o heapSort
cpp -I../include heapSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o heapSort
Comando para ejecutar:
.\heapSort.exe
*/

/**
 * @brief Heap Sort implementado se basa en el uso de una cola de prioridad "priorityQueue". 
 * El código utiliza un "heap" con estructura de árbol binario que va actualizándose dependiendo de la comparación entre nodos padre-hijo. 
 * Mientras se van insertando los valores en el heap, se usa "swap" para intercambiar los valores. 
 * Lo mismo ocurre al extraer el primer elemento de la cola de prioridad (extractPriority). 
 * Este método está basado en lo implementado en el archivo heapsort_v1 visto en el ramo.
 */

void heapSort(std::bitset<32>* arreglo, int n) {
    priorityQueue pq;

    // Etapa 1: Insertar elementos en la cola de prioridad
    for (int i = 0; i < n; i++) {
        pq.insert(arreglo[i]);
    }

    // Etapa 2: Extraer elementos en orden
    for (int i = 0; i < n; i++) {
        arreglo[i] = pq.extractPriority();
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
    OpcionesMenu opciones = mostrar_menu("Heap_Sort");
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
        heapSort(arreglo, n);
        auto fin = std::chrono::high_resolution_clock::now();

        double duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count() * 1e-9;

        // Verifica si el tiempo fue cero
        if (duracion == 0.0) {
            std::cerr << "Tiempo cero en ejecucion " << i + 1 << ", repitiendo...\n";
            delete[] arreglo;
            --i;  // Repetir la misma iteración
            continue;
        }

        tiempos_individuales.push_back(duracion);
        tiempo_total += duracion;

        if (!esta_ordenado(arreglo, n)) {
            std::cerr << "Error: El arreglo no quedó ordenado en la ejecución " << i + 1 << "\n";
        }

        delete[] arreglo;
    }
    crear_csv_resultados(opciones.ruta_csv, opciones, tiempos_individuales, tiempo_total, "Heap_Sort");

    std::cout << "Ordenamiento completado con exito.\n";
    std::cout << "Resultados guardados en: " << opciones.ruta_csv << "\n";

    return 0;
}
