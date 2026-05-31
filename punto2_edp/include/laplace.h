/**
 * @file laplace.h
 * @brief Definición de la interfaz del módulo de solución de la ecuación de Laplace 2D.
 * @author Tomás A. Peñuela Z. y Juan P. Ospina G.
 * @date 3 de Junio de 2026
 * @details Este archivo actúa como interfaz pública exponiendo los prototipos de 
 * las funciones requeridas para ejecutar el solver numérico de la ecuación de Laplace.
 */

#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

/**
 * @struct ParametrosLaplace
 * @brief Estructura que encapsula los parámetros de la ecuación de Laplace.
 */
struct ParametrosLaplace {
    double L;       ///< Ancho del dominio espacial (m)
    double H;       ///< Alto del dominio espacial (m)
    double h;       ///< Espaciamiento de la malla (m)
    double V0, V1, V2, V3;  ///< Potenciales de frontera (V)
    double omega;   ///< Factor de sobre-relajación (1 < ω < 2)
    double tol;     ///< Tolerancia de convergencia
    int maxIter;    ///< Número máximo de iteraciones
    int nx, ny;     ///< Número de nodos en direcciones x e y
};

/**
 * @struct ResultadosLaplace
 * @brief Estructura que almacena los resultados de la simulación.
 */
struct ResultadosLaplace {
    int iteraciones;    ///< Número de iteraciones ejecutadas
    double errorFinal;  ///< Error máximo final
    bool convergencia;  ///< Indicador de convergencia alcanzada
    double minPhi;      ///< Valor mínimo de φ en el dominio
    double maxPhi;      ///< Valor máximo de φ en el dominio
    double centroPhi;   ///< Valor de φ en el centro del dominio
};

/**
 * @brief Solicita interactivamente los parámetros de la simulación al usuario.
 * @param params Referencia a estructura de parámetros a llenar.
 */
void ingresarParametros(ParametrosLaplace &params);

/**
 * @brief Valida los parámetros ingresados por el usuario.
 * @param params Referencia a estructura de parámetros a validar.
 */
void validarParametros(ParametrosLaplace &params);

/**
 * @brief Aplica las condiciones de frontera Dirichlet a la malla.
 * @param phi Matriz de potenciales.
 * @param params Parámetros con valores de frontera.
 */
void aplicarCondicionesFrontera(std::vector<std::vector<double>> &phi, 
                                 const ParametrosLaplace &params);

/**
 * @brief Resuelve la ecuación de Laplace usando Gauss-Seidel con sobre-relajación.
 * @param phi Matriz de potenciales a actualizar.
 * @param params Parámetros de la simulación.
 * @return ResultadosLaplace Estructura con resultados de la iteración.
 */
ResultadosLaplace resolverLaplace(std::vector<std::vector<double>> &phi, 
                                   const ParametrosLaplace &params);

/**
 * @brief Guarda los resultados en un archivo .dat.
 * @param phi Matriz de potenciales.
 * @param params Parámetros de dominio.
 * @param resultados Resultados de la simulación.
 * @param nombreArchivo Nombre del archivo de salida.
 */
void guardarResultados(const std::vector<std::vector<double>> &phi, 
                       const ParametrosLaplace &params,
                       const ResultadosLaplace &resultados,
                       const std::string &nombreArchivo);

/**
 * @brief Imprime los resultados finales en la consola.
 * @param resultados Estructura con resultados a mostrar.
 */
void imprimirResultados(const ResultadosLaplace &resultados);

/**
 * @brief Calcula estadísticas de la solución (mín, máx, centro).
 * @param phi Matriz de potenciales.
 * @param params Parámetros de dominio.
 * @param resultados Referencia a estructura donde almacenar estadísticas.
 */
void calcularEstadisticas(const std::vector<std::vector<double>> &phi,
                         const ParametrosLaplace &params,
                         ResultadosLaplace &resultados);
