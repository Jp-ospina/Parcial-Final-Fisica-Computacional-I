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
from scipy.interpolate import griddata
import sys

x = []
y = []
v = []

with open('punto2_edp\results\solucion_laplace.dat', 'r') as f:
f.readline()
for line in f:
    parts = line.strip().split()

    x.append(float(parts[0]))
    y.append(float(parts[1]))
    v.append(float(parts[2]))

print(f"Loaded {len(x)} data points.")


# Convert lists to numpy arrays
x_np = np.array(x)
y_np = np.array(y)
v_np = np.array(v)

# Create a regular grid to interpolate onto
xi = np.linspace(x_np.min(), x_np.max(), 100)
yi = np.linspace(y_np.min(), y_np.max(), 100)
Xi, Yi = np.meshgrid(xi, yi)

# Interpolate the data onto the grid
Vi = griddata((x_np, y_np), v_np, (Xi, Yi), method='cubic')

print("Data gridded successfully for plotting.")

# Create 3D surface plot
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(Xi, Yi, Vi, cmap='viridis')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('V')
ax.set_title('3D Surface Plot of V(X, Y)')

plt.show()

plt.savefig('results/graficas/python/laplace_3d.png', dpi=150, bbox_inches='tight')
print("Gráfica 3D guardada en results/graficas/python/laplace_3d.png")


plt.figure(figsize=(8, 6))
contour = plt.contourf(Xi, Yi, Vi, levels=50, cmap='viridis')
plt.colorbar(contour, label='V')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Contour Plot of V(X, Y)')
plt.grid(True)
plt.show()

plt.savefig('results/graficas/python/laplace_contour.png', dpi=150, bbox_inches='tight')
print("Mapa de contorno guardado en results/graficas/python/laplace_contour.png")
