#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

// Тестовая функция
double f(double x) {
    return sin(x) * exp(-x / 10.0);
}

// Аналитическая производная (эталон)
double f_deriv_exact(double x) {
    double e = exp(-x / 10.0);
    return e * (cos(x) - 0.1 * sin(x));
}

// 1. Вперёд
double forward_diff(double x, double h) {
    return (f(x + h) - f(x)) / h;
}

// 2. Назад
double backward_diff(double x, double h) {
    return (f(x) - f(x - h)) / h;
}

// 3. Центральная разность
double central_diff(double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

// 4. Рунге-Ромберга (на основе центральной разности)
double romberg_diff(double x, double h) {
    double D_h = central_diff(x, h);
    double D_2h = central_diff(x, 2.0 * h);
    return (4.0 * D_h - D_2h) / 3.0;
}

int main() {
    double x0 = 2.0;
    double exact = f_deriv_exact(x0);

    vector<double> steps = {1e-1, 5e-2, 1e-2, 5e-3, 1e-3, 5e-4, 1e-4, 5e-5, 1e-5};

    ofstream out("deriv_errors.csv");
    out << "h,forward_error,backward_error,central_error,romberg_error\n";
    out << scientific << setprecision(8);

    for (double h : steps) {
        double fwd = forward_diff(x0, h);
        double bwd = backward_diff(x0, h);
        double cen = central_diff(x0, h);
        double rom = romberg_diff(x0, h);

        double err_fwd = fabs(fwd - exact);
        double err_bwd = fabs(bwd - exact);
        double err_cen = fabs(cen - exact);
        double err_rom = fabs(rom - exact);

        out << h << "," << err_fwd << "," << err_bwd << "," << err_cen << "," << err_rom << "\n";
    }

    cout << "Результаты сохранены в deriv_errors.csv\n";
    return 0;
}