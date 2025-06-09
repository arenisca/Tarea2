#include "../include/librerias.hpp"
#include "../include/interfaz_menu.hpp"
#include "../include/cargar_arreglo.hpp"
#include "../include/creador_csv.hpp"

/*
comandos para compilar:
g++ -I../include mergeSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o mergeSort    
c++ -I../include mergeSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o mergeSort
cpp -I../include mergeSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o mergeSort
comando para ejecutar:
.\mergeSort.exe
*/

/**
 * @brief Función merge para combinar dos subarreglos ordenados
 */
void merge(std::bitset<32>* arr, std::bitset<32>* left, int leftSize, 
           std::bitset<32>* right, int rightSize, int inicio) {
    int i = 0, j = 0, k = inicio;
    while (i < leftSize && j < rightSize) {
        arr[k++] = (left[i].to_ulong() <= right[j].to_ulong()) ? left[i++] : right[j++];
    }
    while (i < leftSize) arr[k++] = left[i++];
    while (j < rightSize) arr[k++] = right[j++];
}

/**
 * @brief Implementación recursiva de Merge Sort
 */
void mergeSort(std::bitset<32>* arr, int inicio, int fin) {
    if (inicio >= fin) return;
    int mitad = inicio + (fin-inicio) / 2;
    
    // Sort lado izquierdo
    mergeSort(arr, inicio, mitad); 
    
    // Sort lado derecho
    mergeSort(arr, mitad + 1, fin);

    // Crear arreglos temporales
    std::bitset<32>* leftArr = new std::bitset<32>[mitad-inicio+1];
    std::bitset<32>* rightArr = new std::bitset<32>[fin-mitad];
    
    // Copiar datos a los arreglos temporales
    for (int i = 0; i < mitad-inicio+1; i++) leftArr[i] = arr[inicio + i];
    for (int i = 0; i < fin-mitad; i++) rightArr[i] = arr[mitad + 1 + i];
    
    // Combinar los arreglos ordenados
    merge(arr, leftArr, mitad-inicio+1, rightArr, fin-mitad, inicio);
    
    // Liberar memoria
    delete[] leftArr;
    delete[] rightArr;
}

bool esta_ordenado(std::bitset<32>* arr, int n) {
    for (int i = 1; i < n; ++i) {
        if (arr[i - 1].to_ulong() > arr[i].to_ulong()) {
            return false;
        }
    }
    return true;
}

int main() {
    OpcionesMenu opciones = mostrar_menu("Merge_Sort");
    int n;
    double tiempo_total = 0;
    std::vector<double> tiempos_individuales;

    for (int i = 0; i < opciones.repeticiones; ++i) {
        std::bitset<32>* arreglo = cargar_arreglo(opciones.nombre_archivo, n);
        if (!arreglo) {
            std::cerr << "Error al cargar el arreglo.\n";
            return 1;
        }

        auto inicio = std::chrono::steady_clock::now();
        mergeSort(arreglo, 0, n-1);
        auto fin = std::chrono::steady_clock::now();

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

    crear_csv_resultados(opciones.ruta_csv, opciones, tiempos_individuales, tiempo_total, "Merge_Sort");

    std::cout << "Ordenamiento completado con exito.\n";
    std::cout << "Resultados guardados en: " << opciones.ruta_csv << "\n";

    return 0;
}