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
        long double ans = atan2(cross_product(b), dot_product(b));
        if (ans < 0) {
            ans += 2 * M_PI;
        }
        return ans;
    }
    Vector r_vector() const {
        return Vector(-x, -y);
    }
    Vector p_vector() const {
        return Vector(-y, x);
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
long double EPS = 1e-9;

long double circ_s(long double r) {
    return M_PI * r * r;
}
long double prop(Vector a, Vector b, long double r) {
    return abs(a.angle(b)) * circ_s(r) / (M_PI * 2);
}

int main() {
    cout.precision(10);
    cout << fixed;

    int n;
    cin >> n;
    vector<Vector> dots(n);
    for (int i = 0; i < n; ++i) {
        cin >> dots[i].x >> dots[i].y;
    }
    Vector s;
    double l;
    cin >> s.x >> s.y >> l;
    int d1, d2;
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        if (abs((s.x - dots[i].x) * (dots[ni].y - dots[i].y)
                - (s.y - dots[i].y) * (dots[ni].x - dots[i].x)) < EPS) {
            d1 = i;
            d2 = ni;
        }
    }
    long double ans = prop(dots[d1] - dots[d2], dots[d2] - dots[d1], l);
    long double l1 = l - (dots[d2] - s).len();
    int f1 = d2, f2 = (d2 + 1) % n, f3 = (d2 + 2) % n;
    while (l1 > 0) {
        Vector v1 = dots[f2] - dots[f1];
        Vector v2 = dots[f3] - dots[f2];
        ans += prop(v1, v2, l1);
        l1 -= (dots[f3] - dots[f2]).len();
        f1 = (f1 + 1) % n;
        f2 = (f2 + 1) % n;
        f3 = (f3 + 1) % n;
    }
    long double l2 = l - (dots[d1] - s).len();
    int h1 = d1, h2 = (d1 - 1) % n, h3 = (d1 - 2) % n;
    while (l1 > 0) {
        Vector v1 = dots[h2] - dots[h1];
        Vector v2 = dots[h3] - dots[h2];
        ans += prop(v1, v2, l2);
        l2 -= (dots[h3] - dots[h2]).len();
        h1 = (h1 - 1) % n;
        h2 = (h2 - 1) % n;
        h3 = (h3 - 1) % n;
    }
    cout << ans;
}