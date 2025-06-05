#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
// por mientras voy a trabajar con arreglos de enteros no serializados
void merge(int* arr, int* left, int leftSize, int* right, int rightSize, int inicio) {
    int i = 0, j = 0, k = inicio;
    while (i < leftSize && j < rightSize) {
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    }
    while (i < leftSize) arr[k++] = left[i++];
    while (j < rightSize) arr[k++] = right[j++];
}
// Recursive Merge Sort function
void mergeSort(int* arr, int inicio, int fin) {
    if (inicio >= fin) return;
    int mitad = inicio + (fin-inicio) / 2;
    // Sort lado izq
    mergeSort(arr, inicio, mitad); 
    // Sort lado derecho
    mergeSort(arr, mitad + 1, fin);

    // creamos arreglos para izq y derecha
    int *leftArr=new int[mitad-inicio+1],*rightArr= new int[fin -mitad];
    // distribuimos los valores
    for (int i = 0; i < mitad-inicio +1; i++) leftArr[i] = arr[inicio + i];
    for (int i = 0; i < fin-mitad; i++) rightArr[i] = arr[mitad + 1 + i];
    // aplicamos la función merge que ordenará los arreglos hasta fusionarlos
    merge(arr,leftArr,mitad-inicio+1,rightArr, fin-mitad, inicio); 
    
}


int main(int argc, char** argv) {
    // Verificación (opcional)
     // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); // Almacenará la cantidad de elementos
    
    // Llenamos el arreglo a ordenar con valores aleatorios 
    int *arreglo = new int[n];
    for(int i=0; i < n; i++) {
        arreglo[i] = rand() % 1000;
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
  

    // imprimimos los primeros 10 elementos para saber si están en orden
    std::cout << "Primeros 10 elementos ordenados: ";
    for (int i = 0; i < 10 && i < n; i++) {
        std::cout << arreglo[i] << " ";
    }

    return 0;
}