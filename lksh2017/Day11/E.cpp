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
bool eq_parts(Vector a, Vector b) {
    return a.x * b.x >= 0 && a.y * b.y >= 0;
}

int main() {
    cout.precision(10);
    cout << fixed;

    Vector in[4];
    for (int i = 0; i < 4; ++i) {
       cin >> in[i].x >> in[i].y;
    }
    Vector oa = in[0] - in[1];
    Vector ob = in[2] - in[1];
    Vector om = in[3] - in[1];

    auto a = oa.cross_product(om);
    auto b = om.cross_product(ob);
    if (a * b >= 0 && om.angle(ob) + om.angle(oa) <= M_PI) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    system("pause");
}