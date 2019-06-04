#include <bits/stdc++.h>
#include "optimization.h"
 
using namespace std;
  
typedef long long ll;
typedef long double ld;
 
const int INF = (int) 1e9 + 1e6 + 123;
const ll LINF = (ll) 1e18 + 1e9 + 123;
const ld EPS = (ld) 1e-7;
const ll MOD = (ll) 1e9 + 7;
 
#define sz(x) (int) (x).size()
#define mp(x, y) make_pair(x, y)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define lb(s, t, x) (int) (lower_bound(s, t, x) - s)
#define ub(s, t, x) (int) (upper_bound(s, t, x) - s)
#define rep(i, f, t) for (int i = f; i < t; i++)
#define per(i, f, t) for (int i = f; i >= t; i--)
 
ll power(ll x, ll y, ll mod = MOD) {
    if (y == 0) {
        return 1;
    }
    if (y & 1) {
        return power(x, y - 1, mod) * x % mod;
    } else {
        ll tmp = power(x, y / 2, mod);
        return tmp * tmp % mod;
    }
}
 
template<typename A, typename B> bool mini(A &x, const B &y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}
 
template<typename A, typename B> bool maxi(A &x, const B &y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}
 
void add(ll &x, ll y) {
	x += y;
	if (x >= MOD) x -= MOD;
	if (x < 0) x += MOD;
}
 
ll mult(ll x, ll y) {
	return x * y % MOD;
}
 
void run();
 
#define TASK ""
 
int main() {
#ifdef LOCAL
    if (strlen(TASK) > 0) {
        cerr << "Reminder: you are using file i/o, filename: " TASK "!" << endl << endl;
    }
#endif
#ifndef LOCAL
    if (strlen(TASK)) {
        freopen(TASK ".in", "r", stdin);
        freopen(TASK ".out", "w", stdout);
    }
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif
    cout << fixed << setprecision(12);
    run();
    return 0;
}
 
// == SOLUTION == //
 
const int N = (int) 1e5 + 123;
const int K = 202;
 
int n, k;
ll a[N];
ll cur[N], nxt[N];
int from[K][N];
 
struct Line {
	ll k, b;
	int id;
	
	ll value(ll x) const {
		return k * x + b;
	}
};
 
ll div_up(ll x, ll y) {
	if (y < 0) {
		x = -x;
		y = -y;
	}
	if (x >= 0) {
		return (x + y - 1) / y;
	} else {
		return x / y;
	}
}
 
ll inter(const Line &a, const Line &b) {
	return div_up(a.b - b.b, b.k - a.k);
}
 
struct Convex {
	vector<Line> lines;
	vector<ll> points;
	int ptr;
	
	Convex() {
		lines.reserve(N);
		points.reserve(N);
	}
	
	void add(const Line &line) {
		while (sz(lines) && lines.back().k == line.k) {
			if (lines.back().b >= line.b) {
				return;
			}
			lines.pop_back();
			if (sz(points)) {
				points.pop_back();
			}
		}
		while (sz(points) && inter(line, lines.back()) <= points.back()) {
			lines.pop_back();
			points.pop_back();
		}
		if (sz(lines)) {
			points.pb(inter(line, lines.back()));
		}
		lines.push_back(line);
		mini(ptr, sz(points));
	}
	
	pair<ll, int> get(ll x) {
		while (ptr < sz(points) && points[ptr] <= x) {
			ptr++;
		}
		return {lines[ptr].value(x), lines[ptr].id};
	}
	
	void clear() {
		ptr = 0;
		lines.clear();
		points.clear();
	}
};
 
Convex cht;
 
void run() {
	n = readInt();
	k = readInt();
	rep(i, 1, n + 1) {
		a[i] = readInt();
	}
	
	fill(nxt, nxt + N, -LINF);
	cur[0] = -LINF;
	
	rep(t, 1, k + 1) {
		cht.clear();
		ll sum = 0;
		rep(i, 1, n + 1) {
			cht.add({sum, cur[i - 1] - sum * sum, i});
			sum += a[i];
			auto res = cht.get(sum);
			nxt[i] = res.first;
			from[t][i] = res.second;
		}
		memcpy(cur, nxt, sizeof cur);
	}
	
	writeInt(cur[n], '\n');
	vector<int> what(k);
	per(i, k, 1) {
		what[i - 1] = from[i][n] - 1;
		n = from[i][n] - 1;
	}
	for (int pos : what) {
		writeInt(pos, ' ');
	}
	writeChar('\n');
}
