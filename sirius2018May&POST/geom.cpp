#include <bits/stdc++.h>

using namespace std;
#define dbl long double
#define ll long long

dbl EPS = 1e-9;


struct vc{
    ll x, y;
    vc() {}

    vc(ll cx, ll cy) {
        x = cx;
        y = cy;
    }
    dbl len() const {
        return hypot(x, y);
    }
    ll dtpr(vc b) const {
        return x * b.x + y * b.y;
    }

    ll crpr(vc b) const {
        return x * b.y - y * b.x;
    }
    dbl angle(vc b) {
        dbl ans = atan2(crpr(b), dtpr(b));
        return ans;
    }
    vc r_vc() const {
        return vc(-x, -y);
    }
    vc p_vc() const {
        return vc(-y, x);
    }
    vc n_vc() const {
        return vc(x / hypot(x, y), y / hypot(x, y));
    }
    const vc operator-(const vc &a) const {
        return vc(x - a.x, y - a.y);
    }
    const vc operator+(const vc &a) const {
        return vc(x + a.x, y + a.y);
    }
    const vc operator*(const dbl &a) const {
        return vc(x * a, y * a);
    }
    const bool operator==(const vc &a) const {
        return y == a.y && x == a.x;
    }
    const bool operator<(const vc &a) const {
        return x < a.x || x == a.x && y < a.y;
    }
};

istream &operator>>(istream &cin, vc &a) {
    cin >> a.x >> a.y;
    return cin;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(30);
    cout << fixed;

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//
//    freopen("intersec4.in", "r", stdin);
//    freopen("intersec4.out", "w", stdout);

    int n;
    cin >> n;
    vector<vc> in(n);
    for(int i = 0; i < n; ++i) {
        cin >> in[i];
    }

    sort(in.begin(), in.end());

    vc l = *in.begin(), r = in.back();
    vector<vc> up, down;
    up.push_back(l);
    down.push_back(l);

    for(int i = 1; i < in.size(); ++i) {
        if(i == in.size() - 1 || (r - l).crpr(in[i] - l) >= 0) {
            while(up.size() >= 2 && (up.back() - up[up.size() - 2]).crpr(in[i] - up.back()) >= 0) {
                up.pop_back();
            }
            up.push_back(in[i]);
        }
        if(i == in.size() - 1 || (r - l).crpr(in[i] - l) <= 0) {
            while(down.size() >= 2 && (down.back() - down[down.size() - 2]).crpr(in[i] - down.back()) <= 0) {
                down.pop_back();
            }
            down.push_back(in[i]);
        }
    }

    for(int i = down.size() - 2; i > 0; --i) {
        up.push_back(down[i]);
    }

    dbl ans = 0;
    for(int i = 0; i < up.size(); ++i) {
        int j = (i + 1) % ((int)up.size());
        ans += (up[j] - up[i]).len();
    }
    cout << ans;
}