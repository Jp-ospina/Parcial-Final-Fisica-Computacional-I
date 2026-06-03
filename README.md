# Examen Final - Física Computacional 1 - Grupo 3

## Autores

- Tomás A. Peñuela Z.
- Juan P. Ospina G.

**Fecha**: 3 de Junio de 2026

## Descripción General

Este proyecto contiene la solución del examen final de Física Computacional I, consistente en dos problemas de modelado numérico:

1. **Punto 1**: Sistemas Acoplados de Lotka-Volterra
2. **Punto 2**: Ecuación de Laplace 2D

Ambos proyectos están implementados de forma modularizada con estructura profesional y documentación completa.

## Compilación y Ejecución

### Uso

**Mostrar menú principal:**
```bash
make
```

**Compilar y ejecutar Punto 1:**
```bash
make punto1
```

**Compilar y ejecutar Punto 2:**
```bash
make punto2
```

**Limpiar archivos:**
```bash
make clean
```

**Ver ayuda:**
```bash
make help
```

## Punto 1: Sistemas Acoplados de Lotka-Volterra

### Descripción

Resuelve dos sistemas depredador-presa de Lotka-Volterra acoplados mediante el método de Runge-Kutta de cuarto orden (RK4).

### Ecuaciones

Sistema 1:
- dx₁/dt = α·x₁ - β·x₁·y₁ + kₓ·(x₂ - x₁)
- dy₁/dt = δ·x₁·y₁ - γ·y₁ + kᵧ·(y₂ - y₁)

Sistema 2:
- dx₂/dt = α·x₂ - β·x₂·y₂ + kₓ·(x₁ - x₂)
- dy₂/dt = δ·x₂·y₂ - γ·y₂ + kᵧ·(y₁ - y₂)

Donde:
- x₁, x₂: poblaciones de presas
- y₁, y₂: poblaciones de depredadores
- α, β, γ, δ: parámetros biológicos
- kₓ, kᵧ: constantes de acoplamiento

## Punto 2: Ecuación de Laplace 2D

### Descripción

Resuelve la ecuación de Laplace bidimensional (∇²φ = 0) en un dominio rectangular usando diferencias finitas y el algoritmo de Gauss-Seidel con sobre-relajación (SOR).

### Método Numérico

**Discretización:**
φᵢ,ⱼ = ¼(φᵢ₊₁,ⱼ + φᵢ₋₁,ⱼ + φᵢ,ⱼ₊₁ + φᵢ,ⱼ₋₁)

**Iteración Gauss-Seidel con SOR:**
φᵢ,ⱼ^(k+1) = (1-ω)φᵢ,ⱼ^(k) + (ω/4)(φᵢ₊₁,ⱼ^(k) + φᵢ₋₁,ⱼ^(k+1) + φᵢ,ⱼ₊₁^(k) + φᵢ,ⱼ₋₁^(k+1))

### Parámetros de Entrada

- **L, H**: dimensiones del dominio
- **h**: espaciamiento de malla
- **V₀, V₁, V₂, V₃**: potenciales de frontera
- **ω**: factor de sobre-relajación (1 < ω < 2)
- **tol**: tolerancia de convergencia
- **maxIter**: número máximo de iteraciones