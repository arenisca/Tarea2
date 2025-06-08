#include "../include/librerias.hpp"

std::vector<int32_t> leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return {};
    }

    // Obtener tamaño del archivo
    archivo.seekg(0, std::ios::end);
    size_t tamanoBytes = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    // Calcular cantidad de enteros (cada uno ocupa 4 bytes)
    size_t numEnteros = tamanoBytes / sizeof(int32_t);
    std::vector<int32_t> arreglo(numEnteros);

    // Leer datos binarios
    archivo.read(reinterpret_cast<char*>(arreglo.data()), tamanoBytes);
    archivo.close();

    return arreglo;
}

void guardarArchivo(const std::string& nombreArchivo, const std::vector<int32_t>& arreglo) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    archivo.write(reinterpret_cast<const char*>(arreglo.data()), arreglo.size() * sizeof(int32_t));
    archivo.close();
}
void insertionSort(std::vector<int32_t>& arreglo) {
    
    for (size_t i = 1; i < arreglo.size(); i++) {
        int32_t clave = arreglo[i];
        int j = i - 1;

        // Mover elementos mayores que la clave hacia la derecha
        while (j >= 0 && arreglo[j] > clave) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = clave; // Insertar en posición correcta
    }
}

int main(int argc, char** argv) {
    // // 1. Leer archivo
    // std::vector<int32_t> datos = leerArchivo("enteros_desordenados.bin");

    // // 2. Ordenar con Insertion Sort
    // insertionSort(datos);

    // // 3. Guardar resultado (opcional)
    // guardarArchivo("enteros_ordenados.bin", datos);

    // Verificación (opcional)
     // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); // Almacenará la cantidad de elementos

    // Llenamos el arreglo a ordenar con valores aleatorios 
    std::bitset<32>* arreglo = new std::bitset<32>[n];
    
    for(int i=0; i < n; i++) {
        arreglo[i]=std::bitset<32> (rand() % 1000);
    }
    // medimos el tiempo que tarda insertSort
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
  

    // imprimimos los primeros 10 elementos para saber si están en orden
    std::cout << "Primeros 10 elementos ordenados: ";
    for (int i = 0; i < 10 && i < n; i++) {
        std::cout << arreglo[i] << " ";
    }
   
    return 0;
}