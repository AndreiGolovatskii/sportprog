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
};

const double INF = 1e9;

double circl_s(double r) {
    return r * r * M_PI;
}


int main() {
    cout.precision(10);
    cout << fixed;

    int n;
    cin >> n;
    vector<Vector> trees(n);
    for (int i = 0; i < n; ++i) {
        cin >> trees[i].x >> trees[i].y;
    }
    vector<double> dist(n, INF);
    for (int i = 0; i < n; ++i) {
        for (int e = 0; e < n; ++e) {
            if (i == e) {
                continue;
            } else {
                double len = (trees[i] - trees[e]).len();
                if (len < dist[i]) {
                    dist[i] = len;
                }
            }
        }
    }

    double ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int e = 0; e < n; ++e) {
            if (i == e) {
                continue;
            }
            double ri = dist[i];
            double re = dist[e];
            if (ri < 1 || re < 1) {
                continue;
            }
            double len = (trees[i] - trees[e]).len();
            ri = min(ri, (double)50);
            re = min(re, (double)50);
            if (len < ri + re) {
                if (re > ri)
                    swap(re, ri); // ri > re
                re = max((double) 1, len - ri);
                ri = len - re;
                ri = min(ri, (double)50);
                re = min(re, (double)50);
            }
            ans = max(ans, circl_s(ri) + circl_s(re));
        }
    }
    cout << ans;
}