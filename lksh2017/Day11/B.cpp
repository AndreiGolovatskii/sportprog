#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

struct Vector{
    double x, y;
    Vector() {}

    Vector(double cx, double cy) {
        x = cx;
        y = cy;
    }
    double len() {
        return hypot(x, y);
    }
    double dot_product(Vector b) {
        return x * b.x + y * b.y;
    }
    double cross_product(Vector b) {
        return x * b.y - y * b.x;
    }
    double angle(Vector b) {
        return abs(atan2(cross_product(b), dot_product(b)));
    }
    const Vector operator-(const Vector &a) const {
        return Vector(x - a.x, y - a.y);
    }
};


double circ_s(int r) {
    return M_PI * r * r;
}
double squa_s(int a) {
    return a * a;
}

double prop(Vector a, Vector b, int r) {
    return a.angle(b) * 2 * circ_s(r) / (M_PI);
}


int main() {
    cout.precision(10);
    cout << fixed;

    int a, r;
    cin >> a >> r;
    double a2 = a / 2.0;

    if (2 * r <= a) {
        cout << circ_s(r);
    } else if (r >= a2 * sqrt(2)) {
        cout << squa_s(a);
    } else {
        double l = sqrt(r * r - a2 * a2);
        double s1 = a2 * l * 4;
        Vector va(l, a2);
        Vector vb(a2, l);
        s1 += prop(va, vb, r);
        cout << s1;
    }
}
