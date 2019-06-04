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
    long double cross_product(Vector b)const {
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
        return x < a.x || (x == a.x && y < a.y);
    }
};
long double EPS = 1e-9;

struct line{
    long double a, b, c;
    line() {}
    line(Vector d1, Vector d2) {
        a = d2.y - d1.y;
        b = d1.x - d2.x;
        c = d1.y * (d2.x - d1.x) - d1.x * (d2.y - d1.y);
    }
    bool is_eq(line l) {
        return abs(a * l.b - b * l.a) < EPS && c == l.c;
    }
    Vector cross(line l) {
        Vector ans;
        ans.y = (a * l.c - l.a * c) / (l.a * b - a * l.b);
        ans.x = (-b * ans.y - c) / a;
        return ans;
    }
};

int main() {
    cout.precision(10);
    cout << fixed;

    Vector in[4];
    for (int i = 0; i < 4; ++i) {
        cin >> in[i].x >> in[i].y;
    }
    if (in[0] == in[1]) {
        if (in[0].x < min(in[2].x, in[3].x) || in[0].x > max(in[2].x, in[3].x) ||
                in[0].y < min(in[2].y, in[3].y) || in[0].y > max(in[2].y, in[3].y)) {
            cout << "Empty";
            return 0;
        }
        cout << in[0].x << " " << in[0].y;
        return 0;
    } else if (in[2] == in[3]) {
        if (in[2].x < min(in[0].x, in[1].x) || in[2].x > max(in[0].x, in[1].x) ||
            in[2].y < min(in[0].y, in[1].y) || in[2].y > max(in[0].y, in[1].y)) {
            cout << "Empty";
            return 0;
        }
        cout << in[2].x << " " << in[2].y;
        return 0;
    }
    if ((in[1] - in[0]).cross_product(in[1] - in[2]) *
            (in[1] - in[0]).cross_product(in[1] - in[3]) > 0 ||
            (in[3] - in[2]).cross_product(in[3] - in[0]) *
            (in[3] - in[2]).cross_product(in[3] - in[1]) > 0) {
        cout << "Empty";
        return 0;
    }
    line l1(in[0], in[1]);
    line l2(in[2], in[3]);
    if (!l1.is_eq(l2)) {
        Vector ans = l1.cross(l2);
        cout << ans.x << " " << ans.y;
        return 0;
    }
    if (in[0] < in[1]) {
        swap(in[0], in[1]);
    }
    if (in[2] < in[3]) {
        swap(in[2], in[3]);
    }
    if (in[0] < in[2]) {
        swap(in[0], in[2]);
        swap(in[1], in[3]);
    }
    if (in[2] == in[1]) {
        cout << in[1].x << " " << in[1].y;
    } else {
        cout << in[1].x << " " << in[1].y << endl;
        cout << in[2].x << " " << in[2].y;
    }
}