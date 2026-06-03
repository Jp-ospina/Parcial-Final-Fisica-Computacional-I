/**
 * @file main.cpp
 * @brief Punto de entrada principal para la simulación del sistema acoplado.
 * @author Tomás A. Peñuela Z. y Juan P. Ospina G.
 * @date 3 de Junio de 2026
 * @details Inicializa la ejecución del programa invocando el solver
 * modularizado del sistema Lotka-Volterra acoplado.
 */

#include "../include/sistema_acoplado.h"

/**
 * @brief Función de entrada principal del programa.
 * @return int Estado de finalización (0 si es exitoso).
 */
int main() {
    simularSistemaAcoplado();
    return 0;
}
