/**
 * @file laplace.cpp
 * @brief Implementación del solver numérico para la ecuación de Laplace 2D.
 * @author Tomás A. Peñuela Z. y Juan P. Ospina G.
 * @date 3 de Junio de 2026
 * @details Contiene la implementación del algoritmo de Gauss-Seidel con 
 * sobre-relajación para resolver la ecuación de Laplace en 2D.
 */

#include "../include/laplace.h"

using namespace std;

/**
 * @brief Implementación de ingresarParametros.
 */
void ingresarParametros(ParametrosLaplace &params) {
    cout << "========== ENTRADA DE PARAMETROS ECUACION DE LAPLACE 2D ==========" << endl;
    
    cout << "\n--- Parametros del Dominio ---" << endl;
    cout << "Ancho del dominio (L) [m]: "; cin >> params.L;
    
    cout << "Alto del dominio (H) [m]: "; cin >> params.H;
    
    cout << "Espaciamiento de malla (h) [m]: "; cin >> params.h;
    
    cout << "\n--- Condiciones de Frontera ---" << endl;
    cout << "Potencial frontera izquierda (V0) [V]: "; cin >> params.V0;
    cout << "Potencial frontera derecha (V1) [V]: "; cin >> params.V1;
    cout << "Potencial frontera inferior (V2) [V]: "; cin >> params.V2;
    cout << "Potencial frontera superior (V3) [V]: "; cin >> params.V3;
    
    cout << "\n--- Parametros del Metodo Iterativo ---" << endl;
    cout << "Factor de sobre-relajacion (omega) [1 < omega < 2]: "; cin >> params.omega;
    cout << "Tolerancia de convergencia: "; cin >> params.tol;
    cout << "Numero maximo de iteraciones: "; cin >> params.maxIter;
}

/**
 * @brief Implementación de validarParametros.
 */
void validarParametros(ParametrosLaplace &params) {
    bool valido = false;
    
    while (!valido) {
        valido = true;
        
        if (params.L <= 0) {
            cout << "Error: L debe ser mayor que cero. Intente de nuevo: ";
            cin >> params.L;
            valido = false;
        }
        
        if (params.H <= 0) {
            cout << "Error: H debe ser mayor que cero. Intente de nuevo: ";
            cin >> params.H;
            valido = false;
        }
        
        if (params.h <= 0) {
            cout << "Error: h debe ser mayor que cero. Intente de nuevo: ";
            cin >> params.h;
            valido = false;
        }
        
        if (params.omega <= 1.0 || params.omega >= 2.0) {
            cout << "Error: omega debe estar en (1, 2). Intente de nuevo: ";
            cin >> params.omega;
            valido = false;
        }
        
        if (params.tol <= 0) {
            cout << "Error: tolerancia debe ser mayor que cero. Intente de nuevo: ";
            cin >> params.tol;
            valido = false;
        }
        
        if (params.maxIter <= 0) {
            cout << "Error: maxIter debe ser mayor que cero. Intente de nuevo: ";
            cin >> params.maxIter;
            valido = false;
        }
    }
    
    params.nx = (int)(params.L / params.h) + 1;
    params.ny = (int)(params.H / params.h) + 1;
}

void aplicarCondicionesFrontera(vector<vector<double>> &phi, 
                                 const ParametrosLaplace &params) {
    for (int j = 0; j < params.ny; j++) {
        phi[0][j] = params.V0;
        phi[params.nx-1][j] = params.V1;
    }
    
    for (int i = 0; i < params.nx; i++) {
        phi[i][0] = params.V2;
        phi[i][params.ny-1] = params.V3;
    }
}

/**
 * @brief Implementación de resolverLaplace.
 * Aplica el algoritmo de Gauss-Seidel con sobre-relajación.
 */
ResultadosLaplace resolverLaplace(vector<vector<double>> &phi, 
                                   const ParametrosLaplace &params) {
    ResultadosLaplace resultados;
    int iter = 0;
    double error = 1e10;
    
    cout << "Iniciando proceso iterativo Gauss-Seidel...\n" << endl;
    cout << "Iteracion | Error maximo" << endl;
    cout << "----------|---------------" << endl;
    
    while (iter < params.maxIter && error > params.tol) {
        error = 0.0;
        
        for (int j = 1; j < params.ny-1; j++) {
            for (int i = 1; i < params.nx-1; i++) {
                double phi_avg = 0.25 * (phi[i+1][j] + phi[i-1][j] + 
                                         phi[i][j+1] + phi[i][j-1]);
                
                double phi_new = (1.0 - params.omega) * phi[i][j] + params.omega * phi_avg;
                
                double local_error = fabs(phi_new - phi[i][j]);
                error = (local_error > error) ? local_error : error;
                
                phi[i][j] = phi_new;
            }
        }
        
        iter++;
        cout << setw(9) << iter << " | " << scientific << setprecision(6) 
             << error << endl;
        
        if (error <= params.tol) {
            break;
        }
    }
    
    resultados.iteraciones = iter;
    resultados.errorFinal = error;
    resultados.convergencia = (error <= params.tol);
    
    return resultados;
}

/**
 * @brief Implementación de calcularEstadisticas.
 */
void calcularEstadisticas(const vector<vector<double>> &phi,
                         const ParametrosLaplace &params,
                         ResultadosLaplace &resultados) {
    resultados.minPhi = phi[1][1];
    resultados.maxPhi = phi[1][1];
    
    for (int j = 1; j < params.ny-1; j++) {
        for (int i = 1; i < params.nx-1; i++) {
            resultados.minPhi = (phi[i][j] < resultados.minPhi) ? phi[i][j] : resultados.minPhi;
            resultados.maxPhi = (phi[i][j] > resultados.maxPhi) ? phi[i][j] : resultados.maxPhi;
        }
    }
    
    resultados.centroPhi = phi[params.nx/2][params.ny/2];
}

/**
 * @brief Implementación de imprimirResultados.
 */
void imprimirResultados(const ResultadosLaplace &resultados) {
    cout << "\n========== RESULTADOS ==========" << endl;
    cout << "Iteraciones: " << resultados.iteraciones << endl;
    cout << "Error final: " << scientific << setprecision(6) << resultados.errorFinal << endl;
    
    if (resultados.convergencia) {
        cout << "Estado: Convergencia alcanzada\n" << endl;
    } else {
        cout << "Estado: Limite de iteraciones alcanzado\n" << endl;
    }
    cout << "Estadisticas de la solucion:" << endl;
    cout << "  Minimo: " << fixed << setprecision(4) << resultados.minPhi << " V" << endl;
    cout << "  Maximo: " << fixed << setprecision(4) << resultados.maxPhi << " V" << endl;
    cout << "  Centro: " << fixed << setprecision(4) << resultados.centroPhi << " V" << endl;
    cout << "================================\n" << endl;
}

/**
 * @brief Implementación de guardarResultados.
 */
void guardarResultados(const vector<vector<double>> &phi, 
                       const ParametrosLaplace &params,
                       const ResultadosLaplace &resultados,
                       const string &nombreArchivo) {
    ofstream outFile(nombreArchivo);
    
    int step = (int)(0.01 / params.h);
    if (step < 1) step = 1;
    
    for (int j = 0; j < params.ny; j += step) {
        for (int i = 0; i < params.nx; i += step) {
            double x = i * params.h;
            double y = j * params.h;
            outFile << fixed << setprecision(6) << x << "\t" 
                    << y << "\t" << phi[i][j] << endl;
        }
    }
    
    outFile.close();
    cout << "Resultados guardados en '" << nombreArchivo << "'" << endl;
}
