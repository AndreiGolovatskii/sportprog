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
    double v_cos(Vector b) {
        return dot_product(b) / (len() * b.len());
    }
    double v_sin(Vector(b)) {
        return sin(angle(b));
    }
    const Vector operator-(const Vector &a) const {
        return Vector(x - a.x, y - a.y);
    }
};


int main() {
    cout.precision(10);
    cout << fixed;

    Vector vectors[3];
    for (int i = 0; i < 3; ++i) {
        cin >> vectors[i].x >> vectors[i].y;
    }
    double ans = 0;
    for (int i = 0; i < 3; ++i) {
        int i1 = (i + 1) % 3;
        int i2 = (i + 2) % 3;
        Vector a = vectors[i1] - vectors[i];
        Vector b = vectors[i2] - vectors[i];
        ans = max(ans, a.angle(b) * 180 / M_PI);
    }
    cout << ans;
}