#include "../include/librerias.hpp"
#include "../include/interfaz_menu.hpp"
#include "../include/cargar_arreglo.hpp"
#include "../include/creador_csv.hpp"

/*
Comandos para compilar:
g++ -I../include bucketSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o bucketSort
c++ -I../include bucketSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o bucketSort
cpp -I../include bucketSort.cpp interfaz_menu.cpp cargar_arreglo.cpp creador_csv.cpp -o bucketSort
Comando para ejecutar:
.\bucketSort.exe
*/

/**
 * @brief Bucket Sort para arreglos de bitset<32>. Usa buckets dinámicos distribuidos según el valor.
 */
void bucketSort(std::bitset<32>* arreglo, int n) {
    if (n <= 1) return;

    // Determinar el valor máximo
    uint32_t max_val = 0;
    for (int i = 0; i < n; ++i) {
        max_val = std::max(max_val, static_cast<uint32_t>(arreglo[i].to_ulong()));
    }

    // Crear buckets
    int num_buckets = std::sqrt(n);
    std::vector<std::vector<std::bitset<32>>> buckets(num_buckets);

    // Distribuir en buckets
    for (int i = 0; i < n; ++i) {
        uint32_t val = arreglo[i].to_ulong();
        int idx = (val * num_buckets) / (max_val + 1);  // Mapear al bucket correspondiente
        buckets[idx].push_back(arreglo[i]);
    }

    // Ordenar cada bucket y concatenar
    int index = 0;
    for (int i = 0; i < num_buckets; ++i) {
        std::sort(buckets[i].begin(), buckets[i].end(), [](const std::bitset<32>& a, const std::bitset<32>& b) {
            return a.to_ulong() < b.to_ulong();
        });
        for (const auto& val : buckets[i]) {
            arreglo[index++] = val;
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
    OpcionesMenu opciones = mostrar_menu("Bucket_Sort");
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
        bucketSort(arreglo, n);
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
            std::cerr << "Error: El arreglo no quedo ordenado en la ejecucion " << i + 1 << "\n";
            delete[] arreglo;
            --i;
            continue;
        }

        delete[] arreglo;
    }

    crear_csv_resultados(opciones.ruta_csv, opciones, tiempos_individuales, tiempo_total, "Bucket_Sort");

    std::cout << "Ordenamiento completado con exito.\n";
    std::cout << "Resultados guardados en: " << opciones.ruta_csv << "\n";

    return 0;
}
