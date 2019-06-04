#include <bits/stdc++.h>

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
    Vector n_vector() const {
        return Vector(x / hypot(x, y), y / hypot(x, y));
    }
    const Vector operator-(const Vector &a) const {
        return Vector(x - a.x, y - a.y);
    }
    const Vector operator+(const Vector &a) const {
        return Vector(x + a.x, y + a.y);
    }
    const Vector operator*(const double &a) const {
        return Vector(x * a, y * a);
    }
};


int main() {
    cout.precision(10);
    cout << fixed;

    Vector dots[3];
    for (int i = 0; i < 3; ++i) {
        cin >> dots[i].x >> dots[i].y;
    }
    Vector n_vect[2];
    for (int i = 0; i < 2; ++i) {
        int i1 = (i + 1) % 3;
        int i2 = (i + 2) % 3;
        n_vect[i] = (dots[i1] - dots[i]).n_vector() + (dots[i2] - dots[i]).n_vector();
    }
    double t = -(dots[0].cross_product(n_vect[1]) - dots[1].cross_product(n_vect[1]))
                / n_vect[0].cross_product(n_vect[1]);
    Vector ans = dots[0] + n_vect[0] * t;
    cout << ans.x << " " << ans.y;
}
