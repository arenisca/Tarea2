// Compilación: g++ -o heapsort_v1 heapsort_v1.cpp

#include <iostream>
#include <chrono>

#include "priorityQueue.h"

using namespace std;

int main(int argc, char** argv) {
  // Si no hay suficientes argumentos, terminamos la ejecución
  if(argc < 2) {
    cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << endl;
    exit(1);
  }
  int n = atoi(argv[1]); // Almacenará la cantidad de elementos

  // Llenamos el arreglo a ordenar con valores aleatorios 
  int *valores = new int[n];
  for(int i=0; i < n; i++)
    valores[i] = rand() % 1000;

  // for(int i=0; i < 15; i++)
  //   cout << valores[i] << " ";
  // cout << "..." << endl;
  

  // Medimos el tiempo por primera vez
  auto start = chrono::high_resolution_clock::now();

  // Comenzamos la ejecución de heap sort

  // Etapa 1: Añadimos todos los valores a la cola de prioridad
  priorityQueue pq;
  for(int i=0; i < n; i++)
    pq.insert(valores[i]);

  // Etapa 2: Extraemos todos los valores ordenados por prioridad
  for(int i=0; i < n; i++)
    valores[i] = pq.extractPriority();

  // Medimos el tiempo por segunda vez
  auto end = chrono::high_resolution_clock::now();
  
  // Calculamos el tiempo transcurrido
  double running_time = chrono::duration_cast<chrono::nanoseconds>(end -
								   start).count();
 
    running_time *= 1e-9;

    // Imprimimos el resultado
    cout << argv[0] << ";\n" << n << ";" << running_time << endl;
  
  // for(int i=0; i < 15; i++)
  //   cout << valores[i] << " ";
  // cout << "..." << endl;
  
  return 0;
}
