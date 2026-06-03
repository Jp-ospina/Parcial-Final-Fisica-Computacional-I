/**
 * @file sistema_acoplado.cpp
 * @brief Implementación del solver de sistemas depredador-presa acoplados.
 * @author Tomás A. Peñuela Z. y Juan P. Ospina G.
 * @date 3 de Junio de 2026
 * @details Contiene la implementación del algoritmo de Runge-Kutta de cuarto
 * orden para integrar sistemas Lotka-Volterra acoplados.
 */

#include "../include/sistema_acoplado.h"

using namespace std;

/**
 * @brief Implementación de verificarDatos.
 */
bool verificarDatos(const Parametros &p) {
    if (p.alpha <= 0.0) return false;
    if (p.beta <= 0.0) return false;
    if (p.gamma <= 0.0) return false;
    if (p.delta <= 0.0) return false;
    if (p.dt <= 0.0) return false;
    if (p.tf <= 0.0) return false;
    return true;
}

/**
 * @brief Implementación de calcularDerivadas.
 * Variables: Y[0]=x1, Y[1]=y1, Y[2]=x2, Y[3]=y2
 */
void calcularDerivadas(double t, const vector<double> &Y,
                       vector<double> &dYdt, const Parametros &p) {
    (void)t;

    double x1 = Y[0];
    double y1 = Y[1];
    double x2 = Y[2];
    double y2 = Y[3];

    dYdt[0] = p.alpha * x1 - p.beta * x1 * y1 + p.kx * (x2 - x1);
    dYdt[1] = p.delta * x1 * y1 - p.gamma * y1 + p.ky * (y2 - y1);
    dYdt[2] = p.alpha * x2 - p.beta * x2 * y2 + p.kx * (x1 - x2);
    dYdt[3] = p.delta * x2 * y2 - p.gamma * y2 + p.ky * (y1 - y2);
}

/**
 * @brief Implementación de rungeKutta4.
 */
void rungeKutta4(double &t, vector<double> &Y, double dt,
                 const Parametros &p) {
    int n = static_cast<int>(Y.size());

    vector<double> k1(n);
    vector<double> k2(n);
    vector<double> k3(n);
    vector<double> k4(n);
    vector<double> Ytemp(n);

    calcularDerivadas(t, Y, k1, p);

    for (int i = 0; i < n; i++) {
        Ytemp[i] = Y[i] + 0.5 * dt * k1[i];
    }

    calcularDerivadas(t + 0.5 * dt, Ytemp, k2, p);

    for (int i = 0; i < n; i++) {
        Ytemp[i] = Y[i] + 0.5 * dt * k2[i];
    }

    calcularDerivadas(t + 0.5 * dt, Ytemp, k3, p);

    for (int i = 0; i < n; i++) {
        Ytemp[i] = Y[i] + dt * k3[i];
    }

    calcularDerivadas(t + dt, Ytemp, k4, p);

    for (int i = 0; i < n; i++) {
        Y[i] += (dt / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
    }

    t += dt;
}

/**
 * @brief Implementación de guardarDatos.
 */
void guardarDatos(ofstream &archivo, double t,
                  const vector<double> &Y) {
    double errorPresas = fabs(Y[0] - Y[2]);
    double errorDepredadores = fabs(Y[1] - Y[3]);

    archivo << fixed << setprecision(10) << t << " " << Y[0] << " " << Y[1]
            << " " << Y[2] << " " << Y[3] << " " << errorPresas << " "
            << errorDepredadores << "\n";
}

/**
 * @brief Implementación de simularSistemaAcoplado.
 */
void simularSistemaAcoplado() {
    Parametros p;

    p.alpha = 1.0;
    p.beta = 0.10;
    p.gamma = 1.50;
    p.delta = 0.075;

    p.kx = 0.05;
    p.ky = 0.05;

    p.dt = 0.01;
    p.tf = 300.0;

    if (!verificarDatos(p)) {
        cerr << "ERROR: Parametros invalidos.\n";
        return;
    }

    vector<double> Y(4);

    Y[0] = 40.0;   // x1
    Y[1] = 9.0;    // y1
    Y[2] = 30.0;   // x2
    Y[3] = 12.0;   // y2

    ofstream archivo("results/datos_sistema_acoplado.dat");

    if (!archivo) {
        cerr << "ERROR: No se pudo crear archivo de datos.\n";
        return;
    }

    archivo << "# t x1 y1 x2 y2 error_x error_y\n";

    double t = 0.0;

    cout << "\nIniciando simulación del sistema acoplado..." << endl;

    while (t <= p.tf) {
        guardarDatos(archivo, t, Y);
        rungeKutta4(t, Y, p.dt, p);
    }

    archivo.close();

    cout << "\n=====================================\n";
    cout << "Simulacion finalizada correctamente.\n";
    cout << "Archivo generado: results/datos_sistema_acoplado.dat\n";
    cout << "Tiempo final: " << p.tf << "\n";
    cout << "Paso temporal: " << p.dt << "\n";
    cout << "=====================================\n";
}
