#include <cstdio>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
// Guardamos un arreglo de n enteros en un archivo
// void guardar_arreglo(const char *fname, int *arr, int n) {
//   FILE *fout = fopen(fname, "wb");

//   if (!fout) {
//     cout << "Error al abrir el archivo " << fname << endl;
//     exit(EXIT_FAILURE);
//   }

//   // Escribimos los primeros n enteros de arreglo arr en el archivo abierto en
//   // fout
//   fwrite();

//   // Cerramos el stream sobre el cual estábamos escribiendo
//   fclose(fout);
// }
void guardar_arreglo(const char *fname, const std::bitset<32> *arreglo) {
    FILE *archivo = fopen(fname, "wb"); 
    if (!archivo) {
        std::cout << "Error al abrir el archivo." << std::endl;
        exit(EXIT_FAILURE);
    }
    // Escribimos los primeros n enteros de arreglo arr en el archivo abierto en
    // fout
    fwrite(arreglo, sizeof(int32_t), size_t(arreglo), archivo);

    // Cerramos el stream sobre el cual estábamos escribiendo
    fclose(archivo);
}

// Leemos un arreglo de n enteros desde un archivo
std::vector<int32_t> cargar_arreglo(const char *fname, int *n) {
    FILE *archivo = fopen(fname, "rb");    
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return {};
    }

    // Movemos el puntero que apunta al inicio del archivo hasta el final
    fseek(archivo, 0L, SEEK_END);
    // Recuperamos la posición (en cantidad de bytes) del puntero
    n = ftell(archivo);
    // Calculamos la cantidad de enteros del arreglo
    n /= sizeof(int);
    // Restablecemos el puntero al inicio
    fseek(archivo, 0L, SEEK_SET);

    // Reservamos espacio para *n enteros
    std::bitset<32>* arreglo = new std::bitset<32>[n];

    // Calcular cantidad de enteros (cada uno ocupa 4 bytes)
    size_t numEnteros = tamanoBytes / sizeof(int32_t);
    std::vector<int32_t> arreglo(numEnteros);

    // Leer datos binarios
    fread(arreglo, numEnteros,n,archivo)
    archivo.close();

    return arreglo;
}


int main(int argc, char **argv) {
  
    if(argc < 2) {
        cout << "Uso: " << argv[0] << " <archivo de salida> error" << endl;
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]); // Almacenará la cantidad de elementos
    
    // Llenamos el arreglo a ordenar con valores aleatorios 
    std::bitset<32>* arreglo = new std::bitset<32>[n];
    
    for(int i=0; i < n; i++) {
        arreglo[i]=std::bitset<32> (rand() % 1000);
    }

    // Guardamos el arreglo en un archivo
    guardar_arreglo(argv[2], arreglo);

    
    // Leemos un arreglo desde archivo
    std::bitset<32>* arr2 = cargar_arreglo(argv[2],n);
    cout << "Arreglo es: " << endl; 
    for (int i = 0; i < 10 && i < n; i++) {
        cout << arr2[i] << " ";
    }
    

    return EXIT_SUCCESS;
}