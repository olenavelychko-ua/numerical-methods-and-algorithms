#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class SeidelMethod {
public:
	static void equalityAnswer(vector<vector<double>>& arr, vector<double>& b, double& eps, vector <double>& x) {
		int n = arr.size();
		vector<double> temp = { 0.0, 0.0, 0.0, 0.0 };
		int i = 1;
		for (int k = 0; k < n; k++) {
			x[k] = b[k] / arr[k][k];
		}
		while (abs(x[0] - temp[0]) >= eps && abs(x[1] - temp[1]) >= eps && abs(x[2] - temp[2]) >= eps && abs(x[3] - temp[3]) >= eps) {
			vector<double> a = { 0.0, 0.0, 0.0, 0.0 };
			vector<double> r = { 0.0, 0.0, 0.0, 0.0 };
			temp[0] = x[0];
			temp[1] = x[1];
			temp[2] = x[2];
			temp[3] = x[3];
			x[0] = (b[0] - arr[0][1] * x[1] - arr[0][2] * x[2] - arr[0][3] * x[3]) / arr[0][0];
			x[1] = (b[1] - arr[1][0] * x[0] - arr[1][2] * x[2] - arr[1][3] * x[3]) / arr[1][1];
			x[2] = (b[2] - arr[2][0] * x[0] - arr[2][1] * x[1] - arr[2][3] * x[3]) / arr[2][2];
			x[3] = (b[3] - arr[3][0] * x[0] - arr[3][1] * x[1] - arr[3][2] * x[2]) / arr[3][3];

			for (int m = 0; m < n; m++) {
				for (int j = 0; j < n; j++) {
					a[m] = arr[m][j] * x[j] + a[m];
					r[m] = abs(a[m] - b[m]);
				}
			}
			cout << "|x[i + 1] - x[i]|<eps" << endl;
			for (int p = 0; p < n; p++) {
				cout << i << " x" << p + 1 << "=" << x[p] << " " << " r" << p << "=" << fixed << setprecision(6) << r[p] << endl;
			}
			i++;
		}
	}
};

int main() {
	vector<vector<double>> matrixA = { {135.9468, 60.2748, 51.8421, 30.8916}, {60.2748, 47.2458, 20.7275, 12.9515}, {51.8421, 20.7275, 34.7977, 11.8614}, {30.8916, 12.9515, 11.8614, 7.0826} };
	//	vector<vector<double>> matrixA = { {3.81, 0.25, 1.28, 0.75} , {-24.3, -30.08, -0.32, -4.71}, {-0.09, -0.404, 0.909, -0.007}, {-0.516, 1.8, 0.022, 0.33} };
	vector<double> b = { 141.6426, 50.2153, 72.4618, 32.6974 };
	//	vector<double> b = { 4.21, -5.43, 1.173, -0.466};
	vector<double> x = { 0.0, 0.0, 0.0, 0.0 };
	double eps = 0.0001;
	SeidelMethod::equalityAnswer(matrixA, b, eps, x);
}
