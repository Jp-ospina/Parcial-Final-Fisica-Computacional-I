/**
 * @file mainSinModularizar.cpp
 * @brief Solver numérico para la ecuación de Laplace 2D (versión sin modularizar).
 * @author Tomás A. Peñuela Z. y Juan P. Ospina G.
 * @date 3 de Junio de 2026
 * @details Implementación completa y autónoma del algoritmo de Gauss-Seidel
 * con sobre-relajación para resolver la ecuación de Laplace bidimensional.
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * @brief Función de entrada principal del programa.
 * Realiza ingreso de parámetros, validación, resolución y almacenamiento de resultados.
 * @return int Estado de finalización (0 si es exitoso).
 */
int main(){
    double L, H, h;
    double V0, V1, V2, V3;
    double omega, tol;
    int maxIter;
    
    cout << "========== ENTRADA DE PARAMETROS ECUACION DE LAPLACE 2D ==========" << endl;
    
    cout << "\n--- Parametros del Dominio ---" << endl;
    cout << "Ancho del dominio (L) [m]: "; cin >> L;
    while (L <= 0) {
        cout << "Error: L debe ser mayor que cero. Intente de nuevo: "; cin >> L;
    }
    
    cout << "Alto del dominio (H) [m]: "; cin >> H;
    while (H <= 0) {
        cout << "Error: H debe ser mayor que cero. Intente de nuevo: "; cin >> H;
    }
    
    cout << "Espaciamiento de malla (h) [m]: "; cin >> h;
    while (h <= 0) {
        cout << "Error: h debe ser mayor que cero. Intente de nuevo: "; cin >> h;
    }
    cout << "\n--- Condiciones de Frontera ---" << endl;
    cout << "Potencial frontera izquierda (V0) [V]: "; cin >> V0;
    
    cout << "Potencial frontera derecha (V1) [V]: "; cin >> V1;
    
    cout << "Potencial frontera inferior (V2) [V]: "; cin >> V2;
    
    cout << "Potencial frontera superior (V3) [V]: "; cin >> V3;
    
    cout << "\n--- Parametros del Metodo Iterativo ---" << endl;
    cout << "Factor de sobre-relajacion (omega) [1 < omega < 2]: "; cin >> omega;
    while (omega <= 1.0 || omega >= 2.0) {
        cout << "Error: omega debe estar en (1, 2). Intente de nuevo: "; cin >> omega;
    }
    
    cout << "Tolerancia de convergencia: "; cin >> tol;
    while (tol <= 0) {
        cout << "Error: tolerancia debe ser mayor que cero. Intente de nuevo: "; cin >> tol;
    }
    
    cout << "Numero maximo de iteraciones: "; cin >> maxIter;
    while (maxIter <= 0) {
        cout << "Error: maxIter debe ser mayor que cero. Intente de nuevo: "; cin >> maxIter;
    }
    
    
    int nx = (int)(L / h) + 1;
    int ny = (int)(H / h) + 1;
    
    // Inicializar matrices para el potencial
    vector<vector<double>> phi(nx, vector<double>(ny, 0.0));
    
    cout << "\n========== CONFIGURACION FINAL ==========" << endl;
    cout << "Dominio: " << L << " m x " << H << " m" << endl;
    cout << "Malla: " << nx << " x " << ny << " nodos" << endl;
    cout << "Potenciales: V0=" << V0 << ", V1=" << V1 << ", V2=" << V2 << ", V3=" << V3 << endl;
    cout << "Omega=" << omega << ", Tolerancia=" << tol << ", Max iter=" << maxIter << endl;
    cout << "========================================\n" << endl;
    
    // Aplicar condiciones de frontera
    for (int j = 0; j < ny; j++) {
        phi[0][j] = V0;
        phi[nx-1][j] = V1;
    }
    
    for (int i = 0; i < nx; i++) {
        phi[i][0] = V2;
        phi[i][ny-1] = V3;
    }
    
    // Iteración de Gauss-Seidel con sobre-relajación
    int iter = 0;
    double error = 1e10;
    
    cout << "Iniciando proceso iterativo Gauss-Seidel...\n" << endl;
    cout << "Iteracion | Error maximo" << endl;
    cout << "----------|---------------" << endl;
    
    while (iter < maxIter && error > tol) {
        error = 0.0;
        
        for (int j = 1; j < ny-1; j++) {
            for (int i = 1; i < nx-1; i++) {
                double phi_avg = 0.25 * (phi[i+1][j] + phi[i-1][j] + 
                                         phi[i][j+1] + phi[i][j-1]);
                
                double phi_new = (1.0 - omega) * phi[i][j] + omega * phi_avg;
                
                double local_error = fabs(phi_new - phi[i][j]);
                error = (local_error > error) ? local_error : error;
                
                phi[i][j] = phi_new;
            }
        }
        
        iter++;
        cout << setw(9) << iter << " | " << scientific << setprecision(6) 
             << error << endl;
        
        if (error <= tol) {
            break;
        }
    }
    
    cout << "\n========== RESULTADOS ==========" << endl;
    cout << "Iteraciones: " << iter << endl;
    cout << "Error final: " << scientific << setprecision(6) << error << endl;
    
    if (error <= tol) {
        cout << "Estado: Convergencia alcanzada\n" << endl;
    } else {
        cout << "Estado: Limite de iteraciones alcanzado\n" << endl;
    }
    cout << "================================\n" << endl;
    
     // Guardar resultados en archivo
    ofstream outFile("results/solucion_laplace.dat");
    
   // Guardar cada décimo nodo para evitar archivo muy grande
    int step = (int)(0.01 / h);
    if (step < 1) step = 1;
    
    for (int j = 0; j < ny; j += step) {
        for (int i = 0; i < nx; i += step) {
            double x = i * h;
            double y = j * h;
            outFile << fixed << setprecision(6) << x << "\t" 
                    << y << "\t" << phi[i][j] << endl;
        }
    }
    
    outFile.close();
    cout << "Resultados guardados en 'results/solucion_laplace.dat'" << endl;
    
    // Estadísticas de la solución
    cout << "Estadisticas de la solucion:" << endl;
    double minPhi = phi[1][1];
    double maxPhi = phi[1][1];
    
    for (int j = 1; j < ny-1; j++) {
        for (int i = 1; i < nx-1; i++) {
            minPhi = (phi[i][j] < minPhi) ? phi[i][j] : minPhi;
            maxPhi = (phi[i][j] > maxPhi) ? phi[i][j] : maxPhi;
        }
    }
    
    cout << "  Minimo: " << fixed << setprecision(4) << minPhi << " V" << endl;
    cout << "  Maximo: " << fixed << setprecision(4) << maxPhi << " V" << endl;
    cout << "  Centro: " << phi[nx/2][ny/2] << " V" << endl;
    
    return 0;
}