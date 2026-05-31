#!/usr/bin/env python3
"""
@file graficar_laplace.py
@brief Script para visualizar la solución de la ecuación de Laplace 2D.
@author Tomás A. Peñuela Z. y Juan P. Ospina G.
@date 3 de Junio de 2026
@details Genera gráficas 3D y mapas de contorno usando matplotlib
para la visualización de la solución numérica de Laplace.
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

def cargar_datos(nombre_archivo):
    """
    @brief Carga los datos del archivo .dat generado por el solver.
    @param nombre_archivo Ruta del archivo de datos.
    @return tuple (x, y, phi) Arrays numpy con coordenadas y potenciales.
    """
    try:
        datos = np.loadtxt(nombre_archivo)
        x = datos[:, 0]
        y = datos[:, 1]
        phi = datos[:, 2]
        return x, y, phi
    except FileNotFoundError:
        print(f"Error: No se encontró el archivo {nombre_archivo}")
        sys.exit(1)
    except Exception as e:
        print(f"Error al cargar datos: {e}")
        sys.exit(1)

def graficar_3d(x, y, phi):
    """
    @brief Genera gráfica 3D de la solución.
    @param x Coordenadas x.
    @param y Coordenadas y.
    @param phi Valores del potencial.
    """
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')
    
    x_unique = np.unique(x)
    y_unique = np.unique(y)
    
    X, Y = np.meshgrid(x_unique, y_unique)
    Z = np.zeros_like(X)
    
    for idx, (xi, yi) in enumerate(zip(x, y)):
        i = np.where(x_unique == xi)[0][0]
        j = np.where(y_unique == yi)[0][0]
        Z[j, i] = phi[idx]
    
    surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8)
    ax.set_xlabel('x (m)')
    ax.set_ylabel('y (m)')
    ax.set_zlabel('Potencial φ(x,y) (V)')
    ax.set_title('Solución de Laplace 2D - Vista 3D')
    fig.colorbar(surf, ax=ax, shrink=0.5, label='φ (V)')
    
    plt.savefig('results/graficas/python/laplace_3d.png', dpi=150, bbox_inches='tight')
    print("✓ Gráfica 3D guardada en results/graficas/python/laplace_3d.png")

def graficar_contorno(x, y, phi):
    """
    @brief Genera mapa de contorno de la solución.
    @param x Coordenadas x.
    @param y Coordenadas y.
    @param phi Valores del potencial.
    """
    fig, ax = plt.subplots(figsize=(10, 8))
    
    x_unique = np.unique(x)
    y_unique = np.unique(y)
    
    X, Y = np.meshgrid(x_unique, y_unique)
    Z = np.zeros_like(X)
    
    for idx, (xi, yi) in enumerate(zip(x, y)):
        i = np.where(x_unique == xi)[0][0]
        j = np.where(y_unique == yi)[0][0]
        Z[j, i] = phi[idx]
    
    contour = ax.contourf(X, Y, Z, levels=20, cmap='viridis')
    contour_lines = ax.contour(X, Y, Z, levels=10, colors='black', alpha=0.3, linewidths=0.5)
    ax.clabel(contour_lines, inline=True, fontsize=8)
    
    ax.set_xlabel('x (m)')
    ax.set_ylabel('y (m)')
    ax.set_title('Solución de Laplace 2D - Mapa de Contorno')
    cbar = fig.colorbar(contour, ax=ax, label='φ (V)')
    
    plt.savefig('results/graficas/python/laplace_contour.png', dpi=150, bbox_inches='tight')
    print("✓ Mapa de contorno guardado en results/graficas/python/laplace_contour.png")

def main():
    """
    @brief Función principal que coordina la carga y visualización de datos.
    """
    print("\n" + "="*50)
    print("  Graficador - Ecuación de Laplace 2D (Python)")
    print("="*50 + "\n")
    
    x, y, phi = cargar_datos('results/solucion_laplace.dat')
    
    print(f"Datos cargados: {len(x)} puntos")
    print(f"Rango de x: [{x.min():.4f}, {x.max():.4f}]")
    print(f"Rango de y: [{y.min():.4f}, {y.max():.4f}]")
    print(f"Rango de φ: [{phi.min():.4f}, {phi.max():.4f}]\n")
    
    print("Generando gráficas...\n")
    graficar_3d(x, y, phi)
    graficar_contorno(x, y, phi)
    
    print("\n✓ Proceso completado exitosamente")
    print("="*50 + "\n")

if __name__ == "__main__":
    main()
