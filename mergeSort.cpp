#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <bitset>

/**
 * @brief mergeSort es el método que se encargará de dividir el arreglo en dos mitades: una izquierda y otra derecha. 
 * Mientras los arreglos sigan teniendo más de dos elementos, se dividirá cada uno en otros dos sub arreglos de forma recursiva. 
 * @brief merge es el paso de conquista, cada uno de los sub arreglos se irá ordenando hasta unirse y así hasta llegar a ordenar y fusionar
 * los dos primeros sub arreglos. Como lo vimos en clase, puede ser visto como un arbol, donde los sub arreglos son las hojas, hasta llegar 
 * a la raíz del árbol (el arreglo original)
 * @param arr es el arreglo raíz desde donde comenzaremos a dividir 
 * @param inicio es la posición o índice de inicio del arreglo, o sub arreglo con respecto al arreglo desde donde se dividió
 * @param fin posición o índice de término un arreglo o sub arreglo
 * @param left sub arreglo izquierdo de la división
 * @param right sub arreglo derecho de la división
 * @param leftSize tamaño del sub arreglo izquierdo
 * @param rightSize tamaño del sub arreglo derecho
 */

void merge(std::bitset<32>* arr, std::bitset<32>* left, int leftSize, std::bitset<32>* right, int rightSize, int inicio) {
    int i = 0, j = 0, k = inicio;
    while (i < leftSize && j < rightSize) {
        arr[k++] = (left[i].to_ulong() <= right[j].to_ulong()) ? left[i++] : right[j++];
    }
    while (i < leftSize) arr[k++] = left[i++];
    while (j < rightSize) arr[k++] = right[j++];
}
// Merge Sort recursiva
void mergeSort(std::bitset<32>* arr, int inicio, int fin) {
    if (inicio >= fin) return;
    int mitad = inicio + (fin-inicio) / 2;
    // Sort lado izq
    mergeSort(arr, inicio, mitad); 
    // Sort lado derecho
    mergeSort(arr, mitad + 1, fin);

    // creamos arreglos para izquierda y derecha
    std::bitset<32>* leftArr= new std::bitset<32>[mitad-inicio+1];
    std::bitset<32>* rightArr= new std::bitset<32>[fin -mitad];
    // distribuimos los valores del arreglo en los subarreglos
    for (int i = 0; i < mitad-inicio +1; i++) leftArr[i] = arr[inicio + i];
    for (int i = 0; i < fin-mitad; i++) rightArr[i] = arr[mitad + 1 + i];
    // aplicamos la función merge que ordenará los arreglos hasta fusionarlos
    merge(arr,leftArr,mitad-inicio+1,rightArr, fin-mitad, inicio); 
    
}
// carga de archivo del arreglo serializado
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
    if(argc < 1) {
        std::cerr << "Usage: " << argv[0] << " <archivo serializado.bin>" << std::endl;
        exit(1);
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
    mergeSort(arreglo,0,n-1); 
    // medimos el tiempo transcurrido aquí por segunda vez
    auto end = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
 
    running_time *= 1e-9;

    // Imprimimos el resultado
    std::cout << argv[0] << ";\n" << n << ";" << running_time << std::endl;

    return 0;
}