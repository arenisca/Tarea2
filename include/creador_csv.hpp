#ifndef CREADOR_CSV_HPP
#define CREADOR_CSV_HPP

#include <string>
#include <vector>
#include "interfaz_menu.hpp"
#include "librerias.hpp"

void crear_csv_resultados(const std::string& ruta_csv, const OpcionesMenu& opciones,
                         const std::vector<double>& tiempos_individuales, double tiempo_total);

#endif