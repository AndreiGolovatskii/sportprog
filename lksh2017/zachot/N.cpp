#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int INF=1e9;
const long double EPS = 1e-9;

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
    Vector n_vector() const {
        return Vector(x / hypot(x, y), y / hypot(x, y));
    }
    const Vector operator-(const Vector &a) const {
        return Vector(x - a.x, y - a.y);
    }
    const Vector operator+(const Vector &a) const {
        return Vector(x + a.x, y + a.y);
    }
    const bool operator<(const Vector &a) const {
        return x < a.x || (a.x == x && y < a.y);
    }
    const bool operator==(const Vector &a) const {
        return abs(x - a.x) < EPS && abs(y - a.y) < EPS;
    }
};

struct event{
    long double x;
    int type;
    const bool operator<(const event &a) const {
        return x < a.x || (a.x == x && type < a.type);
    }
};

struct line{
    long double a, b, c;
    line (){};
    line(long double x1, long double y1, long double x2, long double y2) {
        a = y2 - y1;
        b = x1 - x2;
        c = y1 * (x2 - x1) + x1 * (y1 - y2);
    }
    line norm(){
        line l;
        l.a = a / hypot(a, b);
        l.b = b / hypot(a, b);
        l.c = c;
        return l;
    }
    long double nul(){
        return -c / a;
    }
    const bool operator<(const line &l) const {
        return a < l.a || a == l.a && b < l.b || a == l.a && b == l.b && c < l.c;
    }
};
int main()
{
    cout.precision(10);
    cout << fixed;
    int n;
    cin >> n;
    map<line, vector<event>> M;
    vector<pair<Vector, Vector>> b;
    for (int i = 0; i < n; i++) {
        Vector s, f;
        cin >> s.x >> s.y >> f.x >> f.y;
        if (f < s)
            swap(f, s);
        line l = line(s.x, s.y, f.x, f.y);
        long double nu = l.nul();
        event ev;
        ev.x = hypot(s.x - nu, s.y);
        ev.type = -1;
        if (M[l].empty())
            M[l] = vector<event>(0);
        M[l].push_back(ev);
        ev.x = hypot(f.x - nu, f.y);
        ev.type = 1;
        M[l].push_back(ev);
    }
    long double ans = 0;
    for (auto i : M) {
        sort(i.second.begin(), i.second.end());
        int bal = 0;
        long double s;
        long double f;
        for (auto e : i.second) {
            if (bal == 0) {
                s = e.x;
            }
            if (bal == 1 && e.type == 1) {
                f = e.x;
                ans = max(ans, f - s);
            }
            bal -= e.type;
        }
    }
    cout << ans;
    system("pause");
}

