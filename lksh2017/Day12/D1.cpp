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
int pnpoly(int npol, float * xp, float * yp, float x, float y)
{
    int c = 0;
    for (int i = 0, j = npol - 1; i < npol; j = i++)
    {
        if ((((yp[i]<=y) && (y<yp[j])) || ((yp[j]<=y) && (y<yp[i]))) &&
            (x > (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
            c = !c;
    }
    return c;
}
int main() {
    cout.precision(10);
    cout << fixed;
    int n, x, y;
    Vector dot_s;
    cin >> n >> x >> y;
    vector<Vector> pol(n);
    float xp[n];
    float yp[n];
    for (int i = 0; i < n; ++i) {
        cin >> xp[i] >> yp[i];
    }
    int cnt = pnpoly(n, xp, yp, x, y);
    if (cnt) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}