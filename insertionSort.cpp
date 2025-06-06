#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <bitset>
/**
 * @authors Lucas Morales, Valentina Serón
 * @brief La implementación de insertion sort usada es in-place. Se basa en el uso de ciclo for y condicional while 
 * para aplicar el método visto en clase. El código genera una clave, la cual corresponde al siguiente elemento del arreglo, 
 * que será usada para comparar si es menor o mayor que los elementos anteriores a esta. 
 * Mientras la clave sea menor que los elementos anteriores, los elementos se irán desplazando a la derecha. 
 * Cuando la clave sea mayor a un elemento, se detiene el condicional while y la clave se inserta en la posición siguiente a los elementos menores. 
 */

std::bitset<32>* cargar_arreglo(const char *fname, int& n) {   
    std::ifstream archivo(fname, std::ios::binary);
    if (!archivo) {
        std::cout << "Error al abrir el archivo: " << fname << std::endl;
        return nullptr; 
    }
    archivo.read(reinterpret_cast<char*>(&n), sizeof(n));

    if (n<=0){ std::cout << "Número inválido de elementos."<< std::endl;}
    // creamos el arreglo
    std::bitset<32>* arreglo=new std::bitset<32>[n];
    unsigned long valor;
    for (int i = 0; i < n; ++i) {
        if (!archivo.read(reinterpret_cast<char*>(&valor), sizeof(valor))) {
            std::cout << "Error al leer el elemento " << i << std::endl;
            delete[] arreglo; 
            return nullptr;
        }
        arreglo[i] = std::bitset<32>(valor);
    }
    archivo.close();

    return arreglo;
}

int main(int argc, char** argv) {
    // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 1) {
        std::cout << "Uso: " << argv[0] << " <archivo de elementos .bin>" << std::endl;
        return EXIT_FAILURE;
    }
    // Leemos un arreglo desde archivo y guardamos en n el número de elementos
    int n;
    std::bitset<32>* arreglo = cargar_arreglo(argv[1], n);
    if(n <= 0 || arreglo == nullptr) {
        std::cerr << "Error: Arreglo vacío o inválido" << std::endl;
        return EXIT_FAILURE;
    }
    
    // medimos el tiempo que tarda Insertion Sort
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 1; i < n; i++) {
        std::bitset<32> clave = arreglo[i];
        int j = i - 1;

        // Mover elementos mayores que la clave hacia la derecha
        while (j >= 0 && arreglo[j].to_ulong() > clave.to_ulong()) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = clave; // Insertar en posición correcta
    }
    // medimos el tiempo transcurrido aquí por segunda vez
    auto end = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
 
    running_time *= 1e-9;

    // Imprimimos el resultado
    std::cout << argv[0] << ";\n" << n << ";" << running_time << std::endl;

    return 0;
}