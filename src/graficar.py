import pandas as pd
import matplotlib.pyplot as plt
import os
import glob
from matplotlib.lines import Line2D

def parse_csv(file_path):
    """Parsea el archivo CSV especial con estructura de secciones"""
    data = {}
    current_section = None
    
    with open(file_path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
                
            if line.endswith(':'):
                current_section = line[:-1]
                data[current_section] = []
                continue
                
            if ';' in line:
                if current_section:
                    data[current_section].append(line)
                else:
                    key, value = line.split(';', 1)
                    data[key] = value.strip()
    
    if 'Tiempos individuales (s)' in data:
        tiempos = []
        for t in data['Tiempos individuales (s)']:
            _, valor = t.split(';')
            tiempos.append(float(valor))
        data['Tiempos_individuales'] = tiempos
        if tiempos:
            data['Tiempo_min'] = min(tiempos)
            data['Tiempo_max'] = max(tiempos)
        
    return data

def select_files(csv_files):
    """Permite al usuario seleccionar qué archivos graficar con validación de entrada"""
    print("\nArchivos CSV encontrados:")
    for i, f in enumerate(csv_files, 1):
        print(f"{i}. {os.path.basename(f)}")
    
    while True:
        print("\nSeleccione los archivos a graficar (Máximo 3) (ej. 1,3 o 1-3 o 1,2,3):")
        print("Ingrese 'todos' para seleccionar todos los archivos")
        selection = input("> ").strip().lower()
        
        # Caso especial: todos
        if selection == 'todos':
            return csv_files
        
        # Validar que la selección no esté vacía
        if not selection:
            print("Error: No ha ingresado ninguna selección. Intente nuevamente.")
            continue
        
        selected = []
        valid = True
        
        # Procesar cada parte de la selección
        for part in selection.split(','):
            part = part.strip()
            try:
                if '-' in part:
                    # Procesar rangos (ej. 1-3)
                    start, end = map(int, part.split('-'))
                    if start > end or start < 1 or end > len(csv_files):
                        print(f"Error: Rango inválido '{part}'. Los números deben estar entre 1 y {len(csv_files)}")
                        valid = False
                        break
                    selected.extend(csv_files[start-1:end])
                else:
                    # Procesar números individuales
                    num = int(part)
                    if num < 1 or num > len(csv_files):
                        print(f"Error: Número inválido '{num}'. Debe estar entre 1 y {len(csv_files)}")
                        valid = False
                        break
                    selected.append(csv_files[num-1])
            except ValueError:
                print(f"Error: Entrada inválida '{part}'. Debe ser un número o rango de números.")
                valid = False
                break
        
        # Verificar si hubo errores
        if not valid:
            continue
            
        # Eliminar duplicados manteniendo el orden
        selected = list(dict.fromkeys(selected))
        
        # Validar cantidad máxima
        if len(selected) > 3:
            print(f"Error: Ha seleccionado {len(selected)} archivos. El máximo permitido es 3.")
            continue
            
        # Validar que se seleccionó al menos uno
        if len(selected) == 0:
            print("Error: No ha seleccionado ningún archivo válido. Intente nuevamente.")
            continue
            
        return selected
def plot_results(selected_files):
    """Genera gráficos para los archivos seleccionados con leyendas y metadatos organizados"""
    plt.figure(figsize=(14, 8))

    base_colors = ['#1f77b4', '#ff7f0e', '#2ca02c']  # Colores base para puntos
    legend_positions = ['upper left', 'upper center', 'upper right']
    
    # Ajustar las posiciones de los cuadros de metadatos para que estén más separados
    metadata_positions = [(1.02, 0.98), (1.02, 0.65), (1.02, 0.3)]
    metadata_vertical_spacing = 0.25  # Espacio vertical entre cuadros de metadatos

    ax = plt.gca()

    for i, csv_file in enumerate(selected_files):
        data = parse_csv(csv_file)
        tiempos = data.get('Tiempos_individuales', [])

        if not tiempos:
            continue

        color = base_colors[i]
        label = f"{os.path.basename(csv_file)}"

        # Gráfico de puntos
        ax.scatter(range(1, len(tiempos) + 1),
                   tiempos,
                   color=color,
                   s=30,
                   alpha=0.8,
                   label=label)

        # Colores únicos por archivo para líneas guía
        color_avg = color  # mismo que los puntos

        # Líneas de guía
        avg_time = float(data.get('Tiempo promedio', '0').replace('s', ''))
        min_time = data.get('Tiempo_min', avg_time)
        max_time = data.get('Tiempo_max', avg_time)

        ax.axhline(y=avg_time, color=color_avg, linestyle='--', alpha=0.8)
        ax.axhline(y=min_time, color=color_avg, linestyle=':', alpha=0.8)
        ax.axhline(y=max_time, color=color_avg, linestyle='-.', alpha=0.8)

        # Cuadro de metadatos
        metadata = [
            f"Archivo: {os.path.basename(csv_file)}",
            f"Algoritmo: {data.get('Algoritmo', 'N/A')}",
            f"Tamaño: {data.get('Tamaño', 'N/A')}",
            f"Orden: {data.get('Orden', 'N/A')}",
            f"Repeticiones: {data.get('Repeticiones', 'N/A')}",
            f"Máquina: {data.get('Máquina', 'N/A')}",
            f"Tiempo total: {data.get('Tiempo total', 'N/A')}",
        ]
        
        # Ajustar la posición vertical basada en el índice
        y_pos = 0.98 - (i * metadata_vertical_spacing)
        
        plt.annotate('\n'.join(metadata),
                     xy=(1.02, y_pos),
                     xycoords='axes fraction',
                     fontsize=9,
                     ha='left',
                     va='top',
                     bbox=dict(boxstyle='round', facecolor='white', alpha=0.8,
                             edgecolor='gray', linewidth=0.5))

        # Leyenda individual para cada archivo
        legend_elements = [
            Line2D([0], [0], marker='o', color='w',
                   label=f"Ejecuciones ({len(tiempos)})",
                   markerfacecolor=color, markersize=8),
            Line2D([0], [0], color=color_avg, linestyle='--', lw=1,
                   label=f'Promedio: {avg_time:.6f}s'),
            Line2D([0], [0], color=color_avg, linestyle=':', lw=1,
                   label=f'Mínimo: {min_time:.6f}s'),
            Line2D([0], [0], color=color_avg, linestyle='-.', lw=1,
                   label=f'Máximo: {max_time:.6f}s')
        ]

        legend = ax.legend(handles=legend_elements,
                           loc=legend_positions[i],
                           framealpha=0.8,
                           title=os.path.basename(csv_file))
        ax.add_artist(legend)

    # Configuración general
    ax.set_title('Tiempos de Ejecución Individuales' +
                 (' (Comparación)' if len(selected_files) > 1 else ''))
    ax.set_xlabel('Número de Ejecución')
    ax.set_ylabel('Tiempo (segundos)')
    ax.grid(True, alpha=0.3)

    # Ajustar los márgenes para dar más espacio a los cuadros de metadatos
    plt.subplots_adjust(right=0.75 if len(selected_files) > 1 else 0.85)
    
    plt.show()

def main():
    base_dir = '../Resultados_CSV/'
    
    # Paso 1: Selección de carpeta
    opciones = ['Lucas', 'Vale']
    print("Seleccione la carpeta de resultados:")
    for i, nombre in enumerate(opciones, start=1):
        print(f"{i}. {nombre}")
    
    seleccion = input("Ingrese el número correspondiente a la máquina: ")
    if not seleccion.isdigit() or int(seleccion) not in [1, 2]:
        print("Selección inválida.")
        return
    
    carpeta_maquina = opciones[int(seleccion) - 1]
    csv_dir = os.path.join(base_dir, carpeta_maquina)

    # Paso 2: Verificación de existencia y archivos
    if not os.path.exists(csv_dir):
        print(f"Error: No se encontró el directorio {csv_dir}")
        return

    csv_files = sorted(glob.glob(os.path.join(csv_dir, '*.csv')))
    if not csv_files:
        print("No se encontraron archivos CSV para graficar en la carpeta seleccionada.")
        return

    # Paso 3: Selección de archivos y graficación
    selected_files = select_files(csv_files)
    if not selected_files:
        print("No se seleccionaron archivos válidos")
        return

    plot_results(selected_files)

if __name__ == "__main__":
    main()