#!/usr/bin/env python3
"""
@file graficar_sistema_acoplado.py
@brief Script para visualizar la solución del sistema acoplado de Lotka-Volterra.
@author Tomás A. Peñuela Z. y Juan P. Ospina G.
@date 3 de Junio de 2026
@details Genera gráficas de dinámicas poblacionales y errores de acoplamiento.
"""

import numpy as np
import matplotlib.pyplot as plt
import sys

def cargar_datos(nombre_archivo):
    """
    @brief Carga los datos del archivo de simulación.
    @param nombre_archivo Ruta del archivo de datos.
    @return tuple (t, x1, y1, x2, y2, error_x, error_y)
    """
    try:
        datos = np.loadtxt(nombre_archivo, skiprows=1)
        t = datos[:, 0]
        x1 = datos[:, 1]
        y1 = datos[:, 2]
        x2 = datos[:, 3]
        y2 = datos[:, 4]
        error_x = datos[:, 5]
        error_y = datos[:, 6]
        return t, x1, y1, x2, y2, error_x, error_y
    except FileNotFoundError:
        print(f"Error: No se encontró el archivo {nombre_archivo}")
        sys.exit(1)
    except Exception as e:
        print(f"Error al cargar datos: {e}")
        sys.exit(1)

def graficar_poblaciones(t, x1, y1, x2, y2):
    """
    @brief Genera gráficas de dinámicas poblacionales.
    @param t Tiempo.
    @param x1, y1 Presas y depredadores del sistema 1.
    @param x2, y2 Presas y depredadores del sistema 2.
    """
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(12, 10))

    ax1.plot(t, x1, 'b-', label='Sistema 1', linewidth=2)
    ax1.plot(t, x2, 'r--', label='Sistema 2', linewidth=2)
    ax1.set_xlabel('Tiempo (t)')
    ax1.set_ylabel('Población de Presas')
    ax1.set_title('Dinámicas de Presas (x1, x2)')
    ax1.legend()
    ax1.grid(True, alpha=0.3)

    ax2.plot(t, y1, 'b-', label='Sistema 1', linewidth=2)
    ax2.plot(t, y2, 'r--', label='Sistema 2', linewidth=2)
    ax2.set_xlabel('Tiempo (t)')
    ax2.set_ylabel('Población de Depredadores')
    ax2.set_title('Dinámicas de Depredadores (y1, y2)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)

    ax3.plot(t, x1, 'b-', label='x1', linewidth=2)
    ax3.plot(t, y1, 'b--', label='y1', linewidth=2)
    ax3.set_xlabel('Tiempo (t)')
    ax3.set_ylabel('Población')
    ax3.set_title('Sistema 1: Presas vs Depredadores')
    ax3.legend()
    ax3.grid(True, alpha=0.3)

    ax4.plot(t, x2, 'r-', label='x2', linewidth=2)
    ax4.plot(t, y2, 'r--', label='y2', linewidth=2)
    ax4.set_xlabel('Tiempo (t)')
    ax4.set_ylabel('Población')
    ax4.set_title('Sistema 2: Presas vs Depredadores')
    ax4.legend()
    ax4.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('results/graficas/python/sistemas_poblacionales.png', dpi=150, bbox_inches='tight')
    print("✓ Gráfica de dinámicas poblacionales guardada")

def graficar_errores(t, error_x, error_y):
    """
    @brief Genera gráficas de errores de acoplamiento.
    @param t Tiempo.
    @param error_x Error en presas.
    @param error_y Error en depredadores.
    """
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

    ax1.semilogy(t, error_x, 'b-', linewidth=2)
    ax1.set_xlabel('Tiempo (t)')
    ax1.set_ylabel('Error |x1 - x2| (escala log)')
    ax1.set_title('Error de Acoplamiento en Presas')
    ax1.grid(True, alpha=0.3, which='both')

    ax2.semilogy(t, error_y, 'r-', linewidth=2)
    ax2.set_xlabel('Tiempo (t)')
    ax2.set_ylabel('Error |y1 - y2| (escala log)')
    ax2.set_title('Error de Acoplamiento en Depredadores')
    ax2.grid(True, alpha=0.3, which='both')

    plt.tight_layout()
    plt.savefig('results/graficas/python/errores_acoplamiento.png', dpi=150, bbox_inches='tight')
    print("✓ Gráfica de errores de acoplamiento guardada")

def graficar_plano_fase(x1, y1, x2, y2):
    """
    @brief Genera plano de fase del sistema.
    @param x1, y1 Órbita del sistema 1.
    @param x2, y2 Órbita del sistema 2.
    """
    fig, ax = plt.subplots(figsize=(10, 8))

    ax.plot(x1, y1, 'b-', label='Sistema 1', linewidth=2, alpha=0.7)
    ax.plot(x2, y2, 'r--', label='Sistema 2', linewidth=2, alpha=0.7)
    ax.plot(x1[0], y1[0], 'bo', markersize=10, label='Inicio 1')
    ax.plot(x2[0], y2[0], 'rs', markersize=10, label='Inicio 2')
    ax.set_xlabel('Presas (x)')
    ax.set_ylabel('Depredadores (y)')
    ax.set_title('Plano de Fase: Sistemas Acoplados de Lotka-Volterra')
    ax.legend()
    ax.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('results/graficas/python/plano_fase.png', dpi=150, bbox_inches='tight')
    print("✓ Gráfica de plano de fase guardada")

def main():
    """
    @brief Función principal que coordina la visualización.
    """
    print("\n" + "="*60)
    print("  Graficador - Sistema Acoplado de Lotka-Volterra (Python)")
    print("="*60 + "\n")

    t, x1, y1, x2, y2, error_x, error_y = cargar_datos('results/datos_sistema_acoplado.dat')

    print(f"Datos cargados: {len(t)} puntos de tiempo")
    print(f"Tiempo: [{t.min():.4f}, {t.max():.4f}]")
    print(f"Presas: x1 ∈ [{x1.min():.2f}, {x1.max():.2f}], x2 ∈ [{x2.min():.2f}, {x2.max():.2f}]")
    print(f"Depredadores: y1 ∈ [{y1.min():.2f}, {y1.max():.2f}], y2 ∈ [{y2.min():.2f}, {y2.max():.2f}]\n")

    print("Generando gráficas...\n")
    graficar_poblaciones(t, x1, y1, x2, y2)
    graficar_errores(t, error_x, error_y)
    graficar_plano_fase(x1, y1, x2, y2)

    print("\n✓ Proceso completado exitosamente")
    print("="*60 + "\n")

if __name__ == "__main__":
    main()
