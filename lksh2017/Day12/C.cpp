#include <bits/stdc++.h>

using namespace std;

struct Vector{
    long double x, y;
    Vector() {}

    Vector(long double cx, long double cy) {
        x = cx;
        y = cy;
    }
    long double len() const {
        return hypot(x, y);
    }
    long double dot_product(Vector b) {
        return x * b.x + y * b.y;
    }
    long double cross_product(Vector b) {
        return x * b.y - y * b.x;
    }
    long double angle(Vector b) {
        return abs(atan2(cross_product(b), dot_product(b)));
    }
    Vector r_vector() const {
        return Vector(-x, -y);
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
    const Vector operator*(const long double &a) const {
        return Vector(x * a, y * a);
    }
    const bool operator==(const Vector &a) const {
        return y == a.y && x == a.x;
    }
    const bool operator<(const Vector &a) const {
        return x < a.x || x == a.x && y < a.y;
    }
};

const long double EPS = 1e-5;

int main() {
    int n;
    cin >> n;
    vector<Vector> dots(n);

    for (int i = 0; i < n; ++i) {
        cin >> dots[i].x >> dots[i].y;
    }
    Vector sides[n];
    for (int i = 0; i < n; ++i) {
        int ni = i + 1;
        if (ni == n) {
            ni = 0;
        }
        Vector side = dots[ni] - dots[i];
        sides[i] = side;
    }
    long double len = sides[0].len();
    long double an = (long double) M_PI * (n - 2) / n;
    for (int i = 0; i < n; ++i) {
        int ni = i + 1;
        if (ni == n) {
            ni = 0;
        }
        if (abs(len - sides[i].len()) > EPS || abs(sides[i].r_vector().angle(sides[ni]) - an) > EPS) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}