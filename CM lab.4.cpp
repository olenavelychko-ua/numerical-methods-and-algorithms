#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class KrylovsMethod {
public:
    static void findingSystem(vector<vector<double>>& arr, vector<vector<double>>& p, vector<double>& b) {
        p = { { 0, 0, 0, 1 },  { 0, 0, 0, 0 },  { 0, 0, 0, 0 },  { 0, 0, 0, 0 } };
        vector<double> y = { 1, 0, 0, 0 };
        vector<double> y1 = { 0, 0, 0, 0 };
        int k = 1;
        for (int l = 3; l >= 0; l--) {
            for (int i = 3; i >= 0; i--) {
                p[i][l] = y[i];
                for (int j = 3; j >= 0; j--) {
                    y1[i] = arr[i][j] * y[j] + y1[i];
                }
            }
            cout << "Vector y" << k << endl;
            k++;
            showVector(y1);
            y = y1;
            y1 = { 0, 0, 0, 0 };
        }
        b = y;
    }

    static void showVector(vector<double>& y) {
        for (int i = 0; i < 4; i++) {
            cout << y[i] << endl;
        }
        cout << endl;
    }
};


int main()
{
    vector<vector<double>> matrixA = { {6.0, 1.10, 0.97, 1.24}, {1.10, 4.00, 1.30, 0.16}, {0.97, 1.30, 5.00, 2.10}, {1.24, 0.16, 2.10, 7.00} };
    ¬¬¬
        vector<vector<double>> p = { { 0, 0, 0, 0 },  { 0, 0, 0, 0 },  { 0, 0, 0, 0 },  { 0, 0, 0, 0 } };
    vector<double> b = { 0, 0, 0, 0 };
    KrylovsMethod::findingSystem(matrixA, p, b);
    cout << "Coefficients of the system" << endl;
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0; j < p.size(); j++) {
            cout << fixed << setprecision(6) << p[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int k = 0; k < b.size(); k++) {
        cout << fixed << setprecision(6) << b[k] << endl;
    }
}
