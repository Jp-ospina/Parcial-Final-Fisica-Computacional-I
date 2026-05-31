# Ecuación de Laplace 2D - Método de Diferencias Finitas con Gauss-Seidel

## Descripción

Este programa resuelve la ecuación de Laplace bidimensional ($\nabla^2 \phi = 0$) en un dominio rectangular usando el método numérico de diferencias finitas con el algoritmo iterativo de Gauss-Seidel y sobre-relajación.

### Características

- **Método Numérico**: Diferencias finitas de segundo orden
- **Solucionador**: Gauss-Seidel con sobre-relajación (SOR)
- **Entrada Interactiva**: Ingreso flexible de parámetros del dominio y condiciones de frontera
- **Validación de Datos**: Verificación automática de parámetros válidos
- **Salida Detallada**: Guardado de resultados en archivo `.dat` en carpeta results/
- **Visualización Dual**: Scripts para graficar con Gnuplot o Python

## Compilación

### Instrucciones

**Compilar:**
```bash
make
```

**Ejecutar simulación:**
```bash
make run
```

**Generar gráficas con Gnuplot:**
```bash
make graficar_gnuplot
```

**Generar gráficas con Python:**
```bash
make graficar_python
```

**Limpiar archivos compilados y resultados:**
```bash
make clean
```

## Parámetros de Entrada

El programa solicita interactivamente los siguientes parámetros:

### Dominio Espacial
- **L**: Ancho del dominio (m)
- **H**: Alto del dominio (m)
- **h**: Espaciamiento de la malla (m)

### Condiciones de Frontera
- **V0**: Potencial en frontera izquierda (V)
- **V1**: Potencial en frontera derecha (V)
- **V2**: Potencial en frontera inferior (V)
- **V3**: Potencial en frontera superior (V)

### Parámetros del Método Iterativo
- **omega**: Factor de sobre-relajación (1 < ω < 2, típicamente ~1.9)
- **tol**: Tolerancia de convergencia (ej: 1e-6)
- **maxIter**: Número máximo de iteraciones (ej: 10000)

## Salida

El programa genera:

1. **Información en consola**:
   - Parámetros ingresados y validados
   - Progreso iterativo (número de iteración y error máximo)
   - Estadísticas finales (mínimo, máximo, valor en el centro)
   - Estado de convergencia

2. **Archivo de datos**:
   - `results/solucion_laplace.dat`: Tres columnas (x, y, φ)

3. **Gráficas** (según opción seleccionada):
   - **Gnuplot**: `results/graficas/gnuplot/`
     - `laplace_3d.png`: Visualización 3D de la solución
     - `laplace_contour.png`: Mapa de contorno
   - **Python**: `results/graficas/python/`
     - `laplace_3d.png`: Superficie 3D con colormap
     - `laplace_contour.png`: Contorno con líneas de nivel

## Método Numérico

La ecuación de Laplace se discretiza usando diferencias finitas de segundo orden:

$$\phi_{i,j} = \frac{1}{4}(\phi_{i+1,j} + \phi_{i-1,j} + \phi_{i,j+1} + \phi_{i,j-1})$$

La iteración de Gauss-Seidel con sobre-relajación es:

$$\phi_{i,j}^{(k+1)} = (1-\omega)\phi_{i,j}^{(k)} + \frac{\omega}{4}(\phi_{i+1,j}^{(k)} + \phi_{i-1,j}^{(k+1)} + \phi_{i,j+1}^{(k)} + \phi_{i,j-1}^{(k+1)})$$

Donde $\omega$ es el factor de sobre-relajación (1 < ω < 2).

## Compilación Alternativa (No Modularizada)

Para compilar la versión sin modularizar:

```bash
cd code
g++ -Wall -O2 -o mainSinModularizar.exe mainSinModularizar.cpp
./mainSinModularizar.exe
```

