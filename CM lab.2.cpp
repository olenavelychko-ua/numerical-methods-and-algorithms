#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class GaussMethod {
public:
	static void findMax(vector<vector<double>> arr, int& l, int& m) {
		int n = arr.size();
		double max = 0.0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (abs(arr[i][j]) > abs(max)) {
					max = arr[i][j];
					l = i;
					m = j;
				}
			}
		}
	}

	static void changeRows(vector<vector<double>>& arr, vector<double>& b, vector<vector<double>>& arr1, vector <double>& b1, vector<double>& koef) {
		int l, m;
		double arr2[4];
		double temp;
		findMax(arr, l, m);
		showMatrix(arr, b);
		int n = arr.size();
		for (int j = 0; j < n; j++) {
			arr2[j] = arr[0][j];
			arr[0][j] = arr[l][j];
			arr[l][j] = arr2[j];
		}
		for (int i = 0; i < n; i++) {
			arr2[i] = arr[i][0];
			arr[i][0] = arr[i][m];
			arr[i][m] = arr2[i];
		}
		swap(b[0], b[l]);
		showMatrix(arr, b);
		temp = arr[0][0];
		for (int i = 0; i < n; i++) {
			if (arr[n - 1][0] != 0) {
				koef[i] = arr[0][i] = arr[0][i] / temp;
			}
			else {
				koef[0] = arr[n - 1][n - 1];
			}
		}
		b[0] = b[0] / temp;
		for (int k = 1; k < n; k++) {
			temp = -arr[k][0];
			for (int i = 0; i < n; i++) {
				arr[k][i] = arr[0][i] * temp + arr[k][i];
			}
			b[k] = b[0] * temp + b[k];
		}
		showMatrix(arr, b);
		if (n != 2) {
			for (int i = 1; i < n; i++) {
				for (int j = 1; j < n; j++) {
					arr1[i - 1][j - 1] = arr[i][j];
				}
				b1[i - 1] = b[i];
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					arr1[i][j] = arr[i][j];
				}
				b1[0] = b[n - 1];
			}
		}
	}

	static void showMatrix(const vector<vector<double>>& arr, const vector<double>& b) {
		int n = arr.size();
		int h = b.size();
		cout << "Matrix A: " << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << fixed << setprecision(6) << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << "Vector b: " << endl;
		for (int i = 0; i < h; i++) {
			cout << fixed << setprecision(6) << b[i] << endl;
		}
		cout << endl;
	}

	static void reverseStroke(vector<vector<double>>& arr, vector<double>& b, vector<double>& x) {
		vector<vector<double>> arr1 = { {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0} };
		vector<vector<double>> arr2 = { {0.0,0.0}, {0.0,0.0} };
		vector<vector<double>> arr3 = { {0.0,0.0}, {0.0,0.0} };
		vector<vector<double>> arr4 = { {0.0,0.0}, {0.0,0.0} };
		vector<double> b1 = { 0.0, 0.0, 0.0 };
		vector<double> b2 = { 0.0,0.0 };
		vector<double> b3 = { 0.0, 0.0 };
		vector<double> b4 = { 0.0 };
		vector<double> a1 = { 0.0, 0.0, 0.0, 0.0 };
		vector<double> a2 = { 0.0, 0.0, 0.0 };
		vector<double> a3 = { 0.0, 0.0 };
		vector<double> a4 = { 0.0 };
		changeRows(arr, b, arr1, b1, a1);
		changeRows(arr1, b1, arr2, b2, a2);
		changeRows(arr2, b2, arr3, b3, a3);
		changeRows(arr3, b3, arr4, b4, a4);

		x[3] = b3[0] / a4[0];
		x[2] = (b2[0] - x[3] * a3[1]) / a3[0];
		x[1] = (b1[0] - x[2] * a2[1] - x[3] * a2[2]) / a2[0];
		x[0] = (b[0] - x[1] * a1[1] - x[2] * a1[2] - x[3] * a1[3]) / a1[0];
	}

	static void review(vector<vector<double>>& arr, vector<double>& b, vector<double>& x, vector<double>& d) {
		vector<double> a = { 0.0, 0.0, 0.0, 0.0 };
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr.size(); j++) {
				a[i] = arr[i][j] * x[j] + a[i];
				d[i] = abs(a[i] - b[i]);
			}
		}
	}
};

int main() {

	vector<vector<double>> matrixA = { {3.81, 0.25, 1.28, 0.75}, {2.25, 1.32, 4.58, 0.49}, {5.31, 6.28, 0.98, 1.04}, {9.39, 2.45, 3.35, 2.28} };
	vector<double> b = { 4.21, 6.47, 2.38, 10.48 };
	vector<double> x = { 0.0, 0.0, 0.0, 0.0 };
	vector<double> d = { 0.0, 0.0, 0.0, 0.0 };
	GaussMethod::reverseStroke(matrixA, b, x);
	cout << "Answer: " << endl;
	for (int i = 0; i < x.size(); i++) {
		cout << "x_" << i << " " << fixed << setprecision(6) << x[i] << endl;
	}
	GaussMethod::review(matrixA, b, x, d);
	cout << "Inconspicuous: " << endl;
	for (int i = 0; i < d.size(); i++) {
		cout << "d_" << i << " " << fixed << setprecision(16) << d[i] << endl;
	}
}
