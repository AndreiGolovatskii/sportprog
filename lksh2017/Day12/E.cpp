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
        return atan2(cross_product(b), dot_product(b));
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

Vector x(1e9, 1e9);

bool cmp(Vector a, Vector b) {
    Vector v1 = a - x;
    Vector v2 = b - x;
    return v1.cross_product(v2) > 0 || v1.cross_product(v2) == 0 && v1.len() < v2.len();
}
long double circ_s(int r) {
    return M_PI * r * 2;
}
long double prop(Vector a, Vector b, int r) {
    return abs(a.angle(b)) * circ_s(r) / (M_PI * 2);
}


int main() {
    cout.precision(10);
    cout << fixed;

    int n;
    long double l;
    cin >> n >> l;
    vector<Vector> dots(n);
    for (int i = 0; i < n; ++i) {
        cin >> dots[i].x >> dots[i].y;
        x = min(x, dots[i]);
    }

    sort(dots.begin(), dots.end(), cmp);
    vector<Vector> ch;
    ch.push_back(dots[0]);
    ch.push_back(dots[1]);
    for (int i = 2; i < n; ++i) {
        while (true) {
            Vector curr = dots[i];
            Vector pr = *ch.rbegin();
            Vector pr2 = *(++ch.rbegin());
            Vector v1 = curr - pr;
            Vector v2 = pr2 - pr;
            if (v1.angle(v2) > 0) {
                ch.push_back(curr);
                break;
            } else {
                ch.erase((--ch.end()));
            }
        }
    }
    long double ans = 0;
    for (size_t i = 0; i < ch.size(); ++i) {
        size_t ni = (i + 1) % ch.size();
        ans += (ch[i] - ch[ni]).len();
        size_t ni2 = (i + 2) % ch.size();
        Vector v1 = (ch[i] - ch[ni]).p_vector();
        Vector v2 = (ch[ni2] - ch[ni]).p_vector().r_vector();
        ans += prop(v1, v2, l);
    }

    cout << ans;
}