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
struct pt {
    long double x, y;
};

long double dist(Vector dot, Vector a, Vector b) {
    Vector v1 = dot - a;
    Vector v2 = dot - b;
    if (v1.cross_product(v2) == 0 && v1.dot_product(v2) <= 0) {
        cout << "YES";
        exit(0);
    }
    return v1.cross_product(v2);
}

bool is_inter(Vector dot_s, Vector dot_f, Vector o1, Vector o2) {
    return (dist(dot_s, o1, o2) * dist(dot_f, o1, o2) < 0 && dist(o1, dot_f, dot_s) * dist(o2, dot_f, dot_s) < 0);
}


int main() {
    cout.precision(10);
    cout << fixed;
    int n;
    Vector dot_s;
    cin >> n >> dot_s.x >> dot_s.y;
    vector<Vector> pol(n);
    for (int i = 0; i < n; ++i) {
        cin >> pol[i].x >> pol[i].y;
        if (pol[i] == dot_s) {
            cout << "YES";
            return 0;
        }
    }
    int cnt = 0;
    Vector dot_f(1e8, 1e8 + 2);
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        if (is_inter(dot_s, dot_f, pol[i], pol[ni])) {
            cnt++;
        }
    }
    if (cnt % 2 == 0) {
        cout << "NO";
    } else {
        cout << "YES";
    }
}