#include <bits/stdc++.h>

using namespace std;

struct Vector{
    double x, y;
    Vector() {}

    Vector(double cx, double cy) {
        x = cx;
        y = cy;
    }
    double len() const {
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
        return y == a.y && x == a.x;
    }
};

const double INF = 1e9;

double dist(Vector dot, Vector a, Vector b) {
    Vector v1 = a - dot;
    Vector v2 = b - dot;
    Vector v3 = a - b;
    return abs(v1.cross_product(v2)) / ( v3.len());
}

int main() {
    cout.precision(3);
    cout << fixed;

    int n, m;
    cin >> n >> m;
    vector<Vector> dots(n);
    vector<Vector> cent(m);
    vector<Vector> napr(m);
    vector<int> rad(m);
    for (int i = 0; i < n; ++i) {
        cin >> dots[i].x >> dots[i].y;
    }
    for (int i = 0; i < m; ++i) {
        cin >> cent[i].x >> cent[i].y;
        cin >> rad[i];
        cin >> napr[i].x >> napr[i].y;
    }
    for (int o = 0; o < m; ++o) {
        int cnt = 0;
        for (int d = 0; d < n; ++d) {
            Vector s = cent[o];
            Vector f = cent[o] + napr[o].n_vector() * 100000;

            Vector ac = dots[d] - s;
            Vector ab = f - s;
            long double distance;
            if (ac.dot_product(ab) <= 0) {
                distance = ac.len();
            } else {
                distance = dist(dots[d], s, f);
            }
            if (distance <= rad[o]) {
                cnt++;
            }
        }
        cout << cnt << " ";
    }
    system("pause");
}