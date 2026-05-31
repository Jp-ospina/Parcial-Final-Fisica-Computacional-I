/**
 * @file main.cpp
 * @brief Punto de entrada principal para la simulación de la ecuación de Laplace 2D.
 * @author Tomás A. Peñuela Z. y Juan P. Ospina G.
 * @date 3 de Junio de 2026
 * @details Este archivo inicializa la ejecución del programa invocando el solver
 * modularizado de la ecuación de Laplace en 2D.
 */

#include "../include/laplace.h"

using namespace std;

/**
 * @brief Función de entrada principal del programa.
 * Orquesta el flujo de entrada, cálculo y almacenamiento de resultados.
 * @return int Estado de finalización (0 si es exitoso).
 */
int main() {
    ParametrosLaplace params;
    
    ingresarParametros(params);
    validarParametros(params);
    
    int nx = params.nx;
    int ny = params.ny;
    
    vector<vector<double>> phi(nx, vector<double>(ny, 0.0));
    
    cout << "\n========== CONFIGURACION FINAL ==========" << endl;
    cout << "Dominio: " << params.L << " m x " << params.H << " m" << endl;
    cout << "Malla: " << nx << " x " << ny << " nodos" << endl;
    cout << "Potenciales: V0=" << params.V0 << ", V1=" << params.V1 
         << ", V2=" << params.V2 << ", V3=" << params.V3 << endl;
    cout << "Omega=" << params.omega << ", Tolerancia=" << params.tol 
         << ", Max iter=" << params.maxIter << endl;
    cout << "========================================\n" << endl;
    
    aplicarCondicionesFrontera(phi, params);
    
    ResultadosLaplace resultados = resolverLaplace(phi, params);
    
    calcularEstadisticas(phi, params, resultados);
    imprimirResultados(resultados);
    
    guardarResultados(phi, params, resultados, "results/solucion_laplace.dat");
    
    return 0;
}
