#include "../include/cargar_arreglo.hpp"
#include <fstream>
#include <iostream>

std::bitset<32>* cargar_arreglo(const std::string& fname, int& n) {
    std::ifstream archivo(fname, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo: " << fname << std::endl;
        return nullptr;
    }

    archivo.seekg(0, std::ios::end);
    std::streampos size = archivo.tellg();
    n = size / sizeof(int);
    archivo.seekg(0, std::ios::beg);

    if (n <= 0) {
        std::cerr << "Número inválido de elementos.\n";
        return nullptr;
    }

    std::bitset<32>* arreglo = new std::bitset<32>[n];
    unsigned int valor;

    for (int i = 0; i < n; ++i) {
        if (!archivo.read(reinterpret_cast<char*>(&valor), sizeof(valor))) {
            std::cerr << "Error al leer el elemento " << i << "\n";
            delete[] arreglo;
            return nullptr;
        }
        arreglo[i] = std::bitset<32>(valor);
    }

    archivo.close();
    return arreglo;
}
