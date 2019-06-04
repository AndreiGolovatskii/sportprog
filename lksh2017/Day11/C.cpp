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
    const Vector operator-(const Vector &a) const {
        return Vector(x - a.x, y - a.y);
    }
    const Vector operator+(const Vector &a) const {
        return Vector(x + a.x, y + a.y);
    }
};

double dist(Vector dot, Vector a, Vector b) {
    Vector v1 = dot - a;
    Vector v2 = dot - b;
    Vector v3 = a - b;
    return abs(v1.cross_product(v2)) / v3.len();
}


int main() {
    cout.precision(10);
    cout << fixed;

    Vector a, b, c;
    int l;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> l;
    double ans;
    Vector ac = c - a;
    Vector ab = b - a;
    Vector bc = c - b;
    Vector ba = a - b;
    if (ac.dot_product(ab) <= 0 || bc.dot_product(ba) <= 0) {
        ans = min(ac.len(), bc.len()) - l;
    } else {
        ans = dist(c, a, b) - l;
    }
    double ans_max = max(ac.len(), bc.len()) - l;
    ans = max(ans, (double)0);
    ans_max = max(ans_max, (double)0);

    cout << ans << endl << ans_max;
}
