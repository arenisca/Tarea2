// Código extraido desde https://www.geeksforgeeks.org/heap-sort/

// Compilación: g++ -o heapsort_v2 heapsort_v2.cpp

#include <iostream>
#include <chrono>

using namespace std;

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int *arr, int N, int i)
{

    // Initialize largest as root
    int largest = i;

    // left = 2*i + 1
    int l = 2 * i + 1;

    // right = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < N && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest
    // so far
    if (r < N && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

// Main function to do heap sort
void heapSort(int *arr, int N)
{

    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--) {

        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

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
  heapSort(valores, n);

  // Medimos el tiempo por segunda vez
  auto end = chrono::high_resolution_clock::now();
  
  // Calculamos el tiempo transcurrido
  double running_time = chrono::duration_cast<chrono::nanoseconds>(end -
								   start).count();
 
    running_time *= 1e-9;

    // Imprimimos el resultado
    cout << argv[0] << ";" << n << ";" << running_time << endl;
  
  // for(int i=0; i < 15; i++)
  //   cout << valores[i] << " ";
  // cout << "..." << endl;

    return 1;
}
