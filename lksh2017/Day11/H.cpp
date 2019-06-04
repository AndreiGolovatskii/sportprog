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
    const bool operator==(const Vector &a) const {
        return x == a.x && y == a.y;
    }
};
bool eq_parts(Vector a, Vector b) {
    return a.x * b.x >= 0 && a.y * b.y >= 0;
}
bool direct(Vector a, Vector b, Vector d) { // d РјРµР¶РґСѓ a Рё b
    auto p = a.cross_product(d);
    auto k = d.cross_product(b);
    if (a == b || a == Vector(-b.x, -b.y)) {
        return d == a || d == b;
    }
    return  (p * k >= 0 && d.angle(b) + d.angle(a) <= M_PI);
}


int main() {
    cout.precision(10);
    cout << fixed;

    Vector curr, fin;

    cin >> curr.x >> curr.y;
    cin >> fin.x >> fin.y;
    Vector f = fin - curr;
    int n;
    cin >> n;
    Vector v[n];
    for (int i = 0; i < n; ++i) {
        cin >> v[i].x >> v[i].y;
        v[i] = v[i].n_vector();
    }
    for (int i = 0; i < n; ++i) {
        for (int e = 0; e < n; ++e) {
            if (v[i] == Vector(-v[i].x, -v[i].y)) {
                continue;
            }
            if (direct(v[i], v[e], f)) {
                cout << "YES";
                return 0;
            }
        }
    }
    if (f.x == 0 && f.y == 0 && n == 0) {
        cout << "YES";
        return 0;
    }
    cout << "NO";
    system("pause");
}