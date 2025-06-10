# Entregable 2: Sorting Death-Match  
**Autores:** Lucas Morales O. & Valentina Serón C.

## Descripción
Este proyecto compara el rendimiento de distintos algoritmos de ordenamiento. Fue diseñado para ejecutarse en sistemas operativos **Windows**. No se garantiza su funcionamiento en otros entornos.

---

## Requisitos del sistema

### C++  
Debe contar con un compilador de C++, como **MinGW**.  
El código hace uso de las siguientes librerías estándar de C++:

```cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <bitset>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <math.h>
#include <algorithm>
```


### Python  
Debe tener instalado un intérprete de Python como python o python3, así como acceso a las siguientes librerías:

Librerías requeridas:
pandas & matplotlib

Use el siguiente comando en la terminal (CMD o shell) para instalar las dependencias:

    pip install pandas matplotlib

---
### Respecto a los archivos de prueba en la carpeta del proyecto 'archivos_de_prueba'

Los 12 archivos archivos binarios (.bin), que podrá apreciar, están nombrados bajo el siguiente criterio, un ejemplo de nombre de archivo es:

    lcp_5000_asc.bin

Este nombre codifica la siguiente información:

-lcp: Hace referencia a la fuente de inspiración del dataset. Proviene del archivo “DBLP-lcp (66MB)”, disponible en 
      http://www.inf.udec.cl/~jfuentess/datasets/sequences.php el cual fue usado para crear nuestros propios archivos de pruebas.
      
-5000: Representa la cantidad de enteros de 32 bits contenidos en el archivo. Los tamaños utilizados fueron:

      {5.000, 50.000, 500.000, 5.000.000}
      
-asc: Indica el orden en que se encuentran los datos dentro del archivo. Se consideraron tres tipos de ordenamiento:

      {asc (ascendente), desc (descendente), shuffled (aleatorio)}
      
Dado que se combinaron los cuatro tamaños con los tres tipos de orden, se generaron un total de 12 archivos distintos.

Los archivos por tamaño tienen el siguiente peso:

    Archivos de 5.000 enteros, 20 KB
    Archivos de 50.000 enteros, 196 KB
    Archivos de 500.000 enteros, 1.954 MB
    Archivos de 5.000.000 enteros, 19.532 MB

---
Compilar y ejecutar códigos
---

### Pasos para ejecutar los archivos de código C++  
(`insertionSort.cpp`, `mergeSort.cpp`, `quickSort.cpp`, `heapSort.cpp`, `radixSort.cpp`, `bucketSort.cpp`):

1. Deberá ingresar a la carpeta 'src' para poder compilar, de otra manera le dirá que no posee los medios para compilar
2. Cada archivo contiene, justo después de las instrucciones `#include`, los comandos necesarios para compilar el código.
3. Debe elegir uno de los tres comandos disponibles para compilar, según el compilador que tenga instalado (`g++`, `c++`, o `cpp`).  
   Ejecute el comando en la terminal (CMD o shell).
4. El comando para ejecutar el programa compilado se encuentra inmediatamente después de los comandos de compilación en el archivo fuente.

---

### Pasos para ejecutar `graficar.py`:

1. Deberá ingresar a la carpeta 'src' para poder compilar, de otra manera le dirá que no posee los medios para compilar
2. El comando para ejecutar el script aparece justo después de los `import` y `from` del archivo.
3. Debe elegir uno de los dos comandos disponibles para ejecutar el script, dependiendo del intérprete instalado:

   ```bash
   python graficar.py
   ```
o

  ```bash
   python3 graficar.py
  ```
---
## Cómo utilizar el código
---

### Si ejecutó uno de los archivos de código en C++

Al iniciar el programa, se mostrará el siguiente menú:

    Seleccione la maquina:
    1. Maquina 1 (Lucas)
    2. Maquina 2 (Vale)

Debes ingresar una opción escribiendo `1` o `2`. Este menú permite identificar la máquina utilizada para diferenciar el rendimiento y atribuir correctamente los resultados obtenidos.

A continuación, se mostrará el siguiente menú para seleccionar el tamaño del arreglo:

    Seleccione el tamano del archivo:
    1. 5000
    2. 50000
    3. 500000
    4. 5000000

Aquí deberás elegir el tamaño del arreglo de enteros (32 bits) con el que deseas realizar la ejecución.

Luego, se desplegará el menú de preordenamiento:

    Seleccione el orden del archivo:
    1. asc
    2. desc
    3. shuffled

Debes seleccionar el tipo de orden inicial que tendrá el arreglo antes de aplicar el algoritmo de ordenamiento.

Finalmente, se pedirá el número de ejecuciones:

    Ingrese el numero de ejecuciones (maximo 10000): 

Puedes ingresar un número entre `1` y `10000`, que indica cuántas veces deseas ejecutar el algoritmo con la configuración seleccionada.

Una vez completado este paso, el programa ejecutará el algoritmo y mostrará el siguiente mensaje de confirmación:

    Ordenamiento completado con exito.
    Resultados guardados en: ../Resultados_CSV/(Máquina escogida)/(Nombre de algoritmo ejecutado)_(Tamaño escogido)_(preordenescogido)_(número de repeticiones).csv
    Por ejemplo:
    Resultados guardados en: ../Resultados_CSV/Radix_Sort_5000000_shuffled_100.csv
---
### Si ejecutó el archivo `grafico.py`

Al iniciar el programa, se mostrará el siguiente menú:

    Seleccione la carpeta de resultados:
    1. Lucas
    2. Vale


La carpeta de resultados corresponde a la máquina desde la cual ejecutaste los algoritmos, tal como se explicó en la sección anterior. Los resultados generados por cada ejecución se guardan en una de estas carpetas.

Luego de seleccionar una carpeta, se mostrará un menú con los distintos archivos CSV disponibles para graficar. Puedes seleccionar hasta un máximo de **3 gráficos**.

⚠️ **Importante:** evita seleccionar archivos con diferentes cantidades de ejecuciones, ya que esto puede distorsionar las gráficas generadas.

Ejemplo del menú que puede aparecer:

    Archivos CSV encontrados:
    1. Bucket_Sort5000_asc_1000_.csv
    2. Bucket_Sort5000_desc_1000_.csv
    3. Bucket_Sort5000_shuffled_1000_.csv
    4. Heap_Sort_5000000_asc_100.csv
    5. Heap_Sort_5000000_desc_100.csv
    6. Heap_Sort_5000000_shuffled_100.csv
    7. Insertion_Sort5000_asc_1000.csv
    8. Insertion_Sort5000_desc_1000.csv
    9. Insertion_Sort5000_shuffled_1000.csv
    10. Merge_Sort_5000000_asc_100.csv
    11. Merge_Sort_5000000_desc_100.csv
    12. Merge_Sort_5000000_shuffled_100.csv
    13. Quick_Sort_500000_shuffled_100.csv
    14. Quick_Sort_50000_asc_100.csv
    15. Quick_Sort_50000_desc_100.csv
    16. Radix_Sort_5000000_asc_100.csv
    17. Radix_Sort_5000000_desc_100.csv
    18. Radix_Sort_5000000_shuffled_100.csv
    
    Seleccione los archivos a graficar (Máximo 3) (ej. 1,3 o 1-3 o 1,2,3):
    > 
Después de ingresar tu selección y presionar Enter, se abrirá automáticamente una ventana que mostrará las gráficas correspondientes a los archivos seleccionados.

---
### Carpeta `gráficos_comparativos`

Esta carpeta contiene archivos `.png` que representan gráficas comparativas para cada algoritmo. En cada imagen se muestran los tres tipos de ordenamientos posibles (ascendente, descendente y aleatorio) combinados en un solo gráfico.

El objetivo de estas gráficas es evidenciar cómo el orden inicial de los datos influye en el rendimiento de los algoritmos de ordenamiento. Un caso especialmente notable es el de **QuickSort**, que muestra un mejor desempeño cuando los datos están aleatoriamente distribuidos. En cambio, si los datos están ordenados de forma ascendente o descendente, la complejidad temporal de QuickSort puede degradarse hasta **O(N²)**.



    
