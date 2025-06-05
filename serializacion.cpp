#include <cstdio>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <fstream>
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
void guardar_arreglo(const char *fname, const std::bitset<32> *arreglo, int n) {
    //FILE *archivo = fopen(fname, "wb"); 
    // Guardar en archivo binario
    std::ofstream archivo(fname, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
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
            cerr << "Error al leer el elemento " << i << endl;
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
        cout << "Uso: " << argv[0] << "<n.ro elementos> <archivo de salida>" << endl;
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]); // Almacenará la cantidad de elementos
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

    
    // Leemos un arreglo desde archivo
    int n_leidos;
    std::bitset<32>* arr2 = cargar_arreglo(argv[2], n_leidos);
    if (arr2 != nullptr) {
        cout << "Primeros 10 elementos del arreglo leído (" << n_leidos << " elementos totales):" << endl; 
        for (int i = 0; i < 10 && i < n_leidos; i++) {
            cout << arr2[i] << " (" << arr2[i].to_ulong() << ")" << endl;
        }
        
        // Liberamos memoria
        delete[] arr2;
    }

    // Liberamos memoria
    delete[] arreglo;

    return EXIT_SUCCESS;
}