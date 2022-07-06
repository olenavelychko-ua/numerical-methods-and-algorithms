#include <iostream>
using namespace std;

class NonlinearEquations {
public:
    static float polynom(float& a) {
        float f_a = 2 * a * a * a * a * a - 2 * a * a * a * a - 4 * a * a * a + 2 * a + 1;
        return f_a;
    }

    static float polynomDeriv(float& a) {
        float f_a = 10 * a * a * a * a - 8 * a * a * a - 12 * a * a + 2;
        return f_a;
    }

    static void bisectionMethod(const float& e, float& a, float& b, float& x, int& i) {
        i = 0;
        float c;

        while (abs(a - b) >= e) {
            c = (a + b) / 2;
            if (polynom(a) * polynom(c) <= 0) b = c;

            else if (polynom(b) * polynom(c) <= 0) a = c;
            cout << " i= " << i << " x= " << (a + b) / 2 << " |a-b|<e " << endl;
            i++;
        }
        x = (a + b) / 2;
    }

    static void chordMethod(const float& e, float& a, float& b, float& x, int& l) {
        l = 1;
        float c = 0;

        c = ((a * polynom(b) - b * polynom(a)) / (polynom(b) - polynom(a)));
        if (polynom(a) * polynom(c) <= 0) {
            while (abs(polynom(c)) >= e) {
                b = c;
                l++;
                c = ((a * polynom(b) - b * polynom(a)) / (polynom(b) - polynom(a)));
                cout << " i= " << l << " x= " << c << " |f(c)|<e " << endl;
            }
        }

        if (polynom(b) * polynom(c) <= 0) {
            while (abs(polynom(c)) >= e) {
                a = c;
                l++;
                c = ((a * polynom(b) - b * polynom(a)) / (polynom(b) - polynom(a)));
                cout << " i= " << l << " x= " << c << " |f(c)|<e " << endl;
            }

        }
        x = c;
    }

    static void NewtonsMethod(const float& e, float& a, float& b, float& x, int& k) {
        k = 1;
        x = 0;
        float x_prew = b;
        x = b - polynom(b) / polynomDeriv(b);
        if (x > b)  x_prew = a;

        x = x - polynom(x) / polynomDeriv(x);

        while (abs(x - x_prew) >= e || abs(polynom(x)) >= e) {

            x_prew = x;
            x = x_prew - polynom(x_prew) / polynomDeriv(x_prew);
            cout << " i= " << k << " x= " << x << " |f(x_k)|<e or |x_k - x_k-1|<e " << endl;
            k++;
        }

    }
};

int main()
{
    float a1 = -2.414;
    float b1 = -0.333;
    float e = 0.0001;
    float x1, x2, x3, y1, y2, y3, z1, z2, z3;
    int i1, i2, i3, l1, l2, l3, k1, k2, k3;
    cout << " Bisection Method: " << endl;

    NonlinearEquations::bisectionMethod(e, a1, b1, x1, i1);
    cout << " i= " << i1 << " x1= " << x1 << " |a-b|<e " << endl;
    cout << "__________________________________________" << endl;

    float a2 = 0.387;
    float b2 = 1.21;
    NonlinearEquations::bisectionMethod(e, a2, b2, x2, i2);
    cout << " i2= " << i2 << " x2= " << x2 << " |a-b|<e " << endl;
    cout << "__________________________________________" << endl;

    float a3 = 1.21;
    float b3 = 2.414;
    NonlinearEquations::bisectionMethod(e, a3, b3, x3, i3);
    cout << " i3= " << i3 << " x3= " << x3 << " |a-b|<e " << endl;
    cout << "__________________________________________" << endl;

    cout << " Chord Method: " << endl;

    float a4 = -2.414;
    float b4 = -0.333;
    NonlinearEquations::chordMethod(e, a4, b4, y1, l1);
    cout << " i= " << l1 << " x1= " << y1 << " |f(c)|<e " << endl;
    cout << "__________________________________________" << endl;

    float a5 = 0.387;
    float b5 = 1.21;
    NonlinearEquations::chordMethod(e, a5, b5, y2, l2);
    cout << " i= " << l2 << " x2= " << y2 << " |f(c)|<e " << endl;
    cout << "__________________________________________" << endl;

    float a6 = 1.21;
    float b6 = 2.414;
    NonlinearEquations::chordMethod(e, a6, b6, y3, l3);
    cout << " i= " << l3 << " x3= " << y3 << " |f(c)|<e " << endl;
    cout << "__________________________________________" << endl;

    cout << " Newton's Method: " << endl;


    float a7 = -2.414;
    float b7 = -0.333;
    NonlinearEquations::NewtonsMethod(e, a7, b7, z1, k1);
    cout << " i= " << k1 << " x1= " << z1 << " |f(x_k)|<e or |x_k - x_k-1|<e " << endl;
    cout << "__________________________________________" << endl;


    float a8 = 0.387;
    float b8 = 1.21;
    NonlinearEquations::NewtonsMethod(e, a8, b8, z2, k2);
    cout << " i= " << k2 << " x2= " << z2 << " |f(x_k)|<e or |x_k - x_k-1|<e " << endl;
    cout << "__________________________________________" << endl;

    float a9 = 1.21;
    float b9 = 2.414;
    NonlinearEquations::NewtonsMethod(e, a9, b9, z3, k3);
    cout << " i= " << k3 << " x3= " << z3 << " |f(x_k)|<e or |x_k - x_k-1|<e " << endl;
    cout << "__________________________________________" << endl;
}
