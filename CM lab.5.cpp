#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
const double PI = 3.1415926535897932384626433832795;

class Interpolation {
public:
	static double fSmall(double x) {
		return (x * x * sin(x));
	}

	static double fBig(const double nodes[], int index, int degree) {
		if (degree == 0)
			return (fSmall(nodes[index + 1]) - fSmall(nodes[index])) / (nodes[index + 1] - nodes[index]);
		else {
			double fOne = fBig(nodes, index + 1, degree - 1);
			double fTwo = fBig(nodes, index, degree - 1);
			return (fOne - fTwo) / (nodes[index + degree + 1] - nodes[index]);
		}
	}

	static double polynom(const double nodes[], const double x[], const double& point) {
		double fInNode = nodes[0];
		int i = 1;
		while (i < 13) {
			double temp = nodes[i];
			for (int k = 0; k < i; k++) {
				temp *= point - x[k];
			}
			fInNode = fInNode + temp;
			i++;
		}
		return fInNode;
	}

	static void findKoefs(const double x[], double a[], double b[], double cRes[], double d[]) {
		const int n = 12;
		double h = PI / 6;
		double c[n][n];
		double c1[n];
		for (int i = 0; i < n; i++) {
			a[i] = Interpolation::fSmall(x[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				c[i][j] = 0;
			}
		}
		c[0][0] = 1;
		c[n - 1][n - 1] = 1;
		for (int i = 1; i < n - 1; i++) {
			c[i][i - 1] = h;
			c[i][i] = 2 * (h + h);
			c[i][i + 1] = h;
		}
		c1[0] = 0;
		c1[n - 1] = 0;
		for (int i = 1; i < n - 1; i++) {
			c1[i] = 3 * (a[i + 1] - 2 * a[i] + a[i - 1]) / h;
		}
		for (int i = 0; i < n - 1; i++) {
			b[i] = ((a[i + 1] - a[i]) / h) - (h / 3) * (cRes[i + 1] + 2 * cRes[i]);
		}
		b[n - 1] = ((a[n - 1] - a[n - 2]) / h - (h / 3) * (2 * cRes[n - 1]));
		for (int i = 0; i < n - 1; i++) {
			d[i] = (cRes[i + 1] - cRes[i]) / (3 * h);
		}
		d[n - 1] = -1 * cRes[n - 1] / (3 * h);
	}

	static double spline(const double& x, double& a, double& b, double& c, double& d, const double& point) {
		double f;
		f = a + b * (point - x) + c * (point - x) * (point - x) + d * (point - x) * (point - x) * (point - x);
		return f;
	}

	static double oversight(const double f[], const double p[]) {
		double max = 0;
		double temp;
		for (int i = 0; i < 12; i++) {
			temp = abs(f[i] - p[i]);
			if (temp > max)  max = temp;
			cout << "f-p " << temp << endl;
		}
		return max;
	}
};

int main() {
	double values[] = { -PI, -5 * PI / 6, -2 * PI / 3,-PI / 2, -PI / 3, -PI / 6, 0, PI / 6, PI / 3, PI / 2, 2 * PI / 3, 5 * PI / 6, PI };
	double valuesPoly[25];
	double resF[14];
	resF[0] = Interpolation::fSmall(values[0]);
	for (int i = 1; i < 13; i++) {
		resF[i] = Interpolation::fBig(values, 0, i - 1);
	}
	valuesPoly[0] = values[0] + PI / 24;
	cout << valuesPoly[0] << endl;
	for (int i = 1; i < 12; i++) {
		valuesPoly[i] = PI / 6 + valuesPoly[i - 1];
		cout << fixed << setprecision(6) << valuesPoly[i] << endl;
	}
	double f[12];
	cout << "Function's values in points: " << endl;
	for (int i = 0; i < 12; i++) {
		f[i] = Interpolation::fSmall(valuesPoly[i]);
		cout << fixed << setprecision(6) << Interpolation::fSmall(valuesPoly[i]) << endl;
	}
	cout << "----------------------------" << endl;
	double resP[12];
	cout << "Polynom's values in points: " << endl;
	for (int i = 0; i < 12; i++) {
		resP[i] = Interpolation::polynom(resF, values, valuesPoly[i]);
		cout << fixed << setprecision(6) << Interpolation::polynom(resF, values, valuesPoly[i]) << endl;
	}
	cout << endl;
	double a[12];
	double b[12];
	double c[] = { 0, 7.688894, 2.675202, 0.248731, -1.631653, -1.437507, -0.01062, 1.479988, 1.482972,  0.30351, -4.735487, 0 };
	double d[12];
	double resS[13];
	cout << "----------------------------" << endl;
	cout << "Spline's values in points: " << endl;
	Interpolation::findKoefs(values, a, b, c, d);
	for (int i = 0; i < 12; i++) {
		resS[i] = Interpolation::spline(values[i], a[i], b[i], c[i], d[i], valuesPoly[i]);
		cout << fixed << setprecision(6) << Interpolation::spline(values[i], a[i], b[i], c[i], d[i], valuesPoly[i]) << endl;
	}
	cout << "----------------------------" << endl;
	double n = Interpolation::oversight(f, resP);
	cout << "Oversight Newton is " << fixed << setprecision(6) << n << endl;
	cout << "----------------------------" << endl;
	double m = Interpolation::oversight(f, resS);
	cout << "Oversight spline is " << fixed << setprecision(6) << m << endl;
}

