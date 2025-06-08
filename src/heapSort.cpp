#include "../include/librerias.hpp"
#include "../include/priorityQueue.hpp"      

/**
 * @brief Heap Sort implementado se basa en el uso de una cola de prioridad "priorityQueue". 
 * El código utiliza un "heap" con estructura de árbol binario que va actualizandose dependiendo de la comparación entre nodos padre-hijo. 
 * Mientras se van insertando los valores en el heap, se usa "swap" para intercambiar los valores. 
 * Lo mismo ocurre al extraer el primer elemento de la cola de prioridad (extractPriority). 
 * Este método está basado en lo implementado en el archivo heapsort_v1 visto en el ramo.
 */

std::bitset<32>* cargar_arreglo(const char *fname, int& n) {
    std::ifstream archivo(fname, std::ios::binary);

    if (!archivo) {
        std::cout << "Error al abrir el archivo: " << fname << std::endl;
        return nullptr; // Retorna vector vacío en caso de error
    }
    archivo.read(reinterpret_cast<char*>(&n), sizeof(n));

    if (n<=0){ std::cout << "Número inválido de elementos."<< std::endl;}

    // creamos el arreglo
    std::bitset<32>* arreglo=new std::bitset<32>[n];
    unsigned long valor;
    for (int i = 0; i < n; ++i) {
        if (!archivo.read(reinterpret_cast<char*>(&valor), sizeof(valor))) {
            std::cout << "Error al leer el elemento " << i << std::endl;
            delete[] arreglo; // Liberamos memoria en caso de error
            return nullptr;
        }
        arreglo[i] = std::bitset<32>(valor);
    }
    archivo.close();

    return arreglo;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <archivo de elementos .bin>" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Leemos un arreglo desde archivo y guardamos el tamaño del arreglo en "n"
    int n; 
    std::bitset<32>* arreglo = cargar_arreglo(argv[1], n);
    if(n <= 0 || arreglo == nullptr) {
        std::cerr << "Error: Arreglo vacío o inválido" << std::endl;
        return EXIT_FAILURE;
    }
    
    // medimos el tiempo que tarda insertSort
    auto start = std::chrono::high_resolution_clock::now();
    // Etapa 1: Añadimos todos los valores del arreglo a la cola de prioridad pq
    priorityQueue pq;
    for(int i=0; i < n; i++) {
        pq.insert(arreglo[i]);
    }
    // Etapa 2: Extraemos todos los valores del arreglo ordenados por prioridad
    for(int i=0; i < n; i++){
        arreglo[i] = pq.extractPriority();
    }
    // medimos el tiempo transcurrido aquí por segunda vez
    auto end = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
 
    running_time *= 1e-9; // recordar que el tiempo está en nano segundos (considerar en el gráfico)

    // Imprimimos el resultado
    std::cout << argv[0] << ";\n" << n << ";" << running_time << std::endl;
 
    return 0;
}