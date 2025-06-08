#ifndef CARGAR_ARREGLO_HPP
#define CARGAR_ARREGLO_HPP

#include "librerias.hpp"

/**
 * @brief Carga un arreglo de enteros desde un archivo binario y lo convierte a un arreglo de bitset de 32 bits.
 * 
 * @param fname Ruta del archivo a leer.
 * @param n Referencia a un entero donde se guardará la cantidad de elementos leídos.
 * @return std::bitset<32>* Arreglo dinámico con los datos cargados (o nullptr en caso de error).
 */
std::bitset<32>* cargar_arreglo(const std::string& fname, int& n);

#endif
