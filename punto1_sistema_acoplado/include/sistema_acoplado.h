/**
 * @file sistema_acoplado.h
 * @brief Definición de la interfaz del módulo de sistemas depredador-presa acoplados.
 * @author Tomás A. Peñuela Z. y Juan P. Ospina G.
 * @date 3 de Junio de 2026
 * @details Expone los prototipos de las funciones para simular dos sistemas
 * Lotka-Volterra acoplados usando Runge-Kutta de cuarto orden.
 */

#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

/**
 * @struct Parametros
 * @brief Estructura que encapsula los parámetros del sistema.
 */
struct Parametros {
    double alpha;   ///< Tasa de crecimiento de presas
    double beta;    ///< Tasa de predación
    double gamma;   ///< Tasa de mortalidad de depredadores
    double delta;   ///< Eficiencia de conversión de alimento
    double kx;      ///< Acoplamiento entre presas
    double ky;      ///< Acoplamiento entre depredadores
    double dt;      ///< Paso de integración temporal
    double tf;      ///< Tiempo final de simulación
};

/**
 * @brief Verifica que los parámetros sean válidos.
 * @param p Parámetros del modelo.
 * @return true si son válidos, false si son inválidos.
 */
bool verificarDatos(const Parametros &p);

/**
 * @brief Calcula las derivadas del sistema acoplado de Lotka-Volterra.
 * @param t Tiempo actual.
 * @param Y Vector de estado [x1, y1, x2, y2].
 * @param dYdt Vector de derivadas.
 * @param p Parámetros del modelo.
 */
void calcularDerivadas(double t, const std::vector<double> &Y,
                       std::vector<double> &dYdt, const Parametros &p);

/**
 * @brief Realiza un paso del método Runge-Kutta de cuarto orden.
 * @param t Tiempo actual (se actualiza).
 * @param Y Vector de estado (se actualiza).
 * @param dt Paso temporal.
 * @param p Parámetros del modelo.
 */
void rungeKutta4(double &t, std::vector<double> &Y, double dt,
                 const Parametros &p);

/**
 * @brief Guarda una fila de datos en el archivo de salida.
 * @param archivo Archivo de salida.
 * @param t Tiempo.
 * @param Y Vector de estado.
 */
void guardarDatos(std::ofstream &archivo, double t,
                  const std::vector<double> &Y);

/**
 * @brief Realiza la simulación completa del sistema.
 */
void simularSistemaAcoplado();
