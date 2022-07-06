#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
const double h = 0.1;
const double PI = 3.1415926535897932384626433832795;
const int s = 48;

class Koshi {
public:
	static double f(double x, double y) {
		return ((1 - x * x) * y + cos(x) - (1 - x * x) * sin(x));
	}

	static void RungeKutta(const double x[], double y[]) {
		double k[4];
		int l = 0;
		y[0] = 0;
		for (int l = 0; l < s - 1; l++) {
			k[0] = h * f(x[l], y[l]);
			k[1] = h * f(x[l] + (h / 2.0), y[l] + (k[0] / 2.0));
			k[2] = h * f(x[l] + (h / 2.0), y[l] + (k[1] / 2.0));
			k[3] = h * f(x[l] + h, y[l] + k[2]);
			y[l + 1] = y[l] + (1.0 / 6.0) * (k[0] + 2.0 * k[1] + 2.0 * k[2] + k[3]);
		}
	}

	static void AdamsBashfort(const double x[], double y[]) {
		double y1[s];
		RungeKutta(x, y1);
		y[0] = y1[0];
		y[1] = y1[1];
		y[2] = y1[2];
		y[3] = y1[3];
		for (int l = 3; l < s - 1; l++) {
			y[l + 1] = y[l] + h * (55.0 * f(x[l], y[l]) - 59.0 * f(x[l - 1], y[l - 1]) + 37.0 * f(x[l - 2], y[l - 2]) - 9.0 * f(x[l - 3], y[l - 3])) / 24.0;
		}
	}

	static double oversight(const double f[], const double p[]) {
		double max = 0;
		for (int i = 0; i < s - 1; i++) {
			double temp;
			temp = abs(f[i] - p[i]);
			if (temp > max)  max = temp;
			cout << "f-p " << temp << endl;
		}
		return max;
	}
};

int main() {
	double x[s];
	double xRes[s];
	cout << fixed << setprecision(6) << "x " << endl;
	x[0] = -PI;
	for (int i = 0; i < s - 1; i++) {
		x[i + 1] = x[i] + h;
		cout << fixed << setprecision(6) << x[i] << endl;
	}
	cout << "y " << endl;
	for (int i = 0; i < s - 1; i++) {
		xRes[i] = sin(x[i]);
		cout << fixed << setprecision(6) << xRes[i] << endl;
	}
	double y[s];
	cout << "Runge-Kutta method" << endl;
	Koshi::RungeKutta(x, y);
	for (int i = 0; i < s - 1; i++) {
		cout << fixed << setprecision(6) << y[i] << endl;
	}
	double y1[s];
	cout << "Adams Bashfort method" << endl;
	Koshi::AdamsBashfort(x, y1);
	for (int i = 0; i < s - 1; i++) {
		cout << fixed << setprecision(6) << y1[i] << endl;
	}
	cout << "----------------------------" << endl;
	double m = Koshi::oversight(y, xRes);
	cout << "Oversight Runge-Kutta method is " << fixed << setprecision(6) << m << endl;
	cout << "----------------------------" << endl;
	double n = Koshi::oversight(y1, xRes);
	cout << "Oversight Adams Bashfort method is " << fixed << setprecision(6) << n << endl;
}




