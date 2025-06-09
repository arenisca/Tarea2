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
    """Permite al usuario seleccionar qué archivos graficar"""
    print("\nArchivos CSV encontrados:")
    for i, f in enumerate(csv_files, 1):
        print(f"{i}. {os.path.basename(f)}")
    
    print("\nSeleccione los archivos a graficar (ej. 1,3 o 1-3 o 'todos'):")
    selection = input("> ").strip().lower()
    
    if selection == 'todos':
        return csv_files
    
    selected = []
    for part in selection.split(','):
        if '-' in part:
            start, end = map(int, part.split('-'))
            selected.extend(csv_files[start-1:end])
        else:
            selected.append(csv_files[int(part)-1])
    
    return selected

def plot_results(selected_files):
    """Genera gráficos para los archivos seleccionados con leyendas y metadatos organizados"""
    plt.figure(figsize=(14, 8))

    base_colors = ['#1f77b4', '#ff7f0e', '#2ca02c']  # Colores base para puntos
    legend_positions = ['upper left', 'upper center', 'upper right']
    metadata_positions = [(1.02, 0.98), (1.02, 0.6), (1.02, 0.2)]

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
        plt.annotate('\n'.join(metadata),
                     xy=metadata_positions[i],
                     xycoords='axes fraction',
                     fontsize=9,
                     ha='left',
                     va='top',
                     bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))

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

    plt.tight_layout()
    output_file = 'grafico_tiempos.png'
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"\nGráfico guardado como: {output_file}")
    plt.show()

def main():
    csv_dir = '../Resultados_CSV'
    if not os.path.exists(csv_dir):
        print(f"Error: No se encontró el directorio {csv_dir}")
        return
    
    csv_files = sorted(glob.glob(os.path.join(csv_dir, '*.csv')))
    if not csv_files:
        print("No se encontraron archivos CSV para graficar")
        return
    
    selected_files = select_files(csv_files)
    if not selected_files:
        print("No se seleccionaron archivos válidos")
        return
    
    plot_results(selected_files)

if __name__ == '__main__':
    main()