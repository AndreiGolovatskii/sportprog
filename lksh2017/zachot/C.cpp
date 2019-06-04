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
    long double dot_product(Vector b)const {
        return x * b.x + y * b.y;
    }
    long double cross_product(Vector b)const {
        return x * b.y - y * b.x;
    }
    long double angle(Vector b)const {
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
        return x < a.x || (x == a.x && y < a.y);
    }
};
long double EPS = 1e-9;

struct triag{
    Vector a, b, c;
    bool is_pd(triag t) {
        long double ang_a1 = (a - b).angle(c - b);
        long double ang_a2 = (b - c).angle(a - c);
        long double ang_a3 = M_PI - ang_a1 - ang_a2;
        long double ang_b1 = (t.a - t.b).angle(t.c - t.b);
        long double ang_b2 = (t.b - t.c).angle(t.a - t.c);
        long double ang_b3 = M_PI - ang_b1 - ang_b2;

        return abs(ang_a1 - ang_b1) < EPS && abs(ang_a2 - ang_b2) < EPS ||
                abs(ang_a1 - ang_b2) < EPS && abs(ang_a2 - ang_b1) < EPS ||
                abs(ang_a1 - ang_b1) < EPS && abs(ang_a3 - ang_b2) < EPS ||
                abs(ang_a2 - ang_b2) < EPS && abs(ang_a3 - ang_b1) < EPS ||
                abs(ang_a1 - ang_b1) < EPS && abs(ang_a3 - ang_b2) < EPS;
    }
};

int main() {
    cout.precision(10);
    cout << fixed;

    triag f;
    cin >> f.a.x >> f.a.y >> f.b.x >> f.b.y >> f.c.x >> f.c.y;


    triag s;
    cin >> s.a.x >> s.a.y >> s.b.x >> s.b.y >> s.c.x >> s.c.y;

    if (s.is_pd(f))
        cout << "YES";
    else
        cout << "NO";
}