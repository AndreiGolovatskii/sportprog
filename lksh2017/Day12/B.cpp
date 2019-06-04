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

double circl_s(double r) {
    return r * r * M_PI;
}
double triag_s(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}


int main() {
    cout.precision(10);
    cout << fixed;

    int l1, l2;
    Vector o1, o2;
    cin >> o1.x >> o1.y >> l1 >> o2.x >> o2.y >> l2;
    if (o1 == o2) {
        if (l1 == l2) {
            cout << 3;
        } else {
            cout << 0;
        }
    } else if (l1 + l2 < (o1 - o2).len()) {
        cout << 0;
    } else if ((o1 - o2).len()  + l1 < l2 || (o1 - o2).len()  + l2 < l1) {
        cout << 0;
    } else {
        double s = triag_s((o1 - o2).len(), l1, l2);
        double h = 2 * s / (o1 - o2).len();
        double dis = sqrt(l1 * l1 - h * h);
        Vector n_v = (o2 - o1).n_vector();
        Vector p1_v = Vector(n_v.y, -n_v.x);
        Vector p2_v = Vector(-n_v.y, n_v.x);
        Vector ans1 = o1 + n_v * dis + p1_v * h;
        Vector ans2 = o1 + n_v * dis + p2_v * h;
        if (ans1 == ans2) {
            cout << 1 << endl;
            cout << ans1.x << " " << ans1.y;
        } else {
            cout << 2 << endl;
            cout << ans1.x << " " << ans1.y << endl << ans2.x << " " << ans2.y;
        }
    }
}