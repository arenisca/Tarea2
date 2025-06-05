#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <bitset>
#include "priorityQueue.h"

// Leemos un arreglo de n enteros desde un archivo
std::bitset<32>* cargar_arreglo(const char *fname, int& n) {
    //FILE *archivo = fopen(fname, "rb");    
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
    // Verificación (opcional)
     // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <archivo de elementos .bin>" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Leemos un arreglo desde archivo
    int n;
    std::bitset<32>* arreglo = cargar_arreglo(argv[1], n);
    if(n <= 0 || arreglo == nullptr) {
        std::cerr << "Error: Arreglo vacío o inválido" << std::endl;
        return EXIT_FAILURE;
    }
    
    // medimos el tiempo que tarda insertSort
    auto start = std::chrono::high_resolution_clock::now();
    // Etapa 1: Añadimos todos los valores a la cola de prioridad
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
  

    //imprimimos los primeros 10 elementos para saber si están en orden
    std::cout << "Primeros 50 elementos ordenados: ";
    for (int i = 0; i < 50 && i < n; i++) {
        std::cout << arreglo[i] << " "<< " (" << arreglo[i].to_ulong() << ")" << std::endl;
    }

    return 0;
}