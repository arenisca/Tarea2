#include <cstdio>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
/**
 * @authors 
 * Valentina Serón
 * Lucas Morales
 * 
 * @brief guardar_arreglo carga un arreglo de enteros serializados para guardarlos en un archivo de estensión .bin
 * @note el arreglo es creado con enteros aleatorios
 * @param fname corresponde al nombre que le daremos al archivo
 * @param arreglo es el arreglo dinámico que contiene los 32 bits de cada entero generado
 * @param n es la cantidad de datos que contiene el arreglo
 */

void guardar_arreglo(const char *fname, const std::bitset<32> *arreglo, int n) {
    // Guardar en archivo binario
    std::ofstream archivo(fname, std::ios::binary);
    if (!archivo) {
        std::cout << "Error al abrir el archivo." << std::endl;
        EXIT_FAILURE;
    }
    // Primero escribimos el número de elementos
    archivo.write(reinterpret_cast<const char*>(&n), sizeof(n));
    // Luego escribimos los datos
    for (int i = 0; i < n; ++i) {
        unsigned long valor = arreglo[i].to_ulong();
        archivo.write(reinterpret_cast<const char*>(&valor), sizeof(valor));
    }

    archivo.close();
    std::cout << "Archivo guardado como "<< fname << std::endl;

}

/**
 * @brief cargar_arreglo: para la lectura de un archivo .bin que contiene un arreglo serializado de tamaño n
 * @param fname es el nombre del archivo .bin
 * @param n es el tamaño de este arreglo
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


int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Uso: " << argv[0] << "<n.ro elementos> <archivo de salida>" << std::endl;
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]); // Almacenará la cantidad de elementos del arreglo
    if(n<=0) {
        std::cout <<"El número de elementos debe ser positivo"<<std::endl;
        return EXIT_FAILURE;
    }
    // Llenamos el arreglo a ordenar con valores aleatorios 
    std::bitset<32>* arreglo = new std::bitset<32>[n];
    
    for(int i=0; i < n; i++) {
        arreglo[i]=std::bitset<32> (rand() % 1000);
    }

    // Guardamos el arreglo en un archivo
    guardar_arreglo(argv[2], arreglo, n);

    /**
     * Las siguientes lineas de código tienen como fin mostrar los 10 primeros elementos del archivo. 
     * No es necesaria su ejecución para el desarrollo de la tarea
     
    int n_leidos;
    std::bitset<32>* arr2 = cargar_arreglo(argv[2], n_leidos);
    if (arr2 != nullptr) {
        std::cout << "Primeros 10 elementos del arreglo leído (" << n_leidos << " elementos totales):" << std::endl; 
        for (int i = 0; i < 10 && i < n_leidos; i++) {
            std::cout << arr2[i] << " (" << arr2[i].to_ulong() << ")" << std::endl;
        }
        
        // Liberamos memoria
        delete[] arr2;
    }
    */

    // Liberamos memoria
    delete[] arreglo;

    return EXIT_SUCCESS;
}