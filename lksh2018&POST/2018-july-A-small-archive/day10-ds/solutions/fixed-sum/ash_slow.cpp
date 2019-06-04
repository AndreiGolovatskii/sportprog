#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <stack>
#include <sstream>
#include <cstring>
#include <numeric>
#include <ctime>
#include <cassert>

#define re return
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define y0 y32479
#define y1 y95874
#define fill(x, y) memset(x, y, sizeof(x))
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define unq(x) (x.resize(unique(all(x)) - x.begin()))
#define spc(i,n) " \n"[i == n - 1]
#define next next239
#define prev prev239

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

template<class T> T abs(T x) { return x > 0 ? x : -x;}

const ll mod = 1000000000 + 7;
const int D = 165;

int n;
int k;

int nint() {
	int x;
	scanf("%d", &x);
	re x;
}

ll sum[100500];
int t[100500];
int a[100500];
int ans[100500 / D + 1][100500];

map<ll, vi> m;

vi v[100500];
ll o[100500];
int cm;

int getSimple(int l, int r) {
	ll tmp = (l ? sum[l - 1] : 0) + k;

	int p = lower_bound(o, o + cm, tmp) - o;
	if (p == cm || o[p] != tmp)
		re 0;

	re upper_bound(all(v[p]), r) - lower_bound(all(v[p]), l);
}

ll getans(int l, int r) {
	ll ans = 0;
	while (l <= r && l % D) {
		ans += getSimple(l, r);
		l++;
	}
	while (l + D - 1 <= r) {
		ans += ::ans[l / D][r];
		l += D;
	}
	while (l <= r) {
		ans += getSimple(l, r);
		l++;
	}
	re ans;
}

int main() {
#ifdef LOCAL_BOBER
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif

	cin >> n >> k;
	rep(i, n)
		t[i] = nint();
	rep(i, n) {
		a[i] = nint();
		if (t[i] == 2)
			a[i] *= -1;
	}

	sum[0] = a[0];
	for (int i = 1; i < n; i++)
		sum[i] = sum[i - 1] + a[i];

	rep(i, n)
		m[sum[i]].pb(i);

	for (auto x : m) {
		o[cm] = x.fi;
		v[cm] = x.se;
		cm++;
	}

	for (int i = 0; i + D <= n; i += D) {
		map<ll, int> mm;
		int o = i / D;
		ll cur = 0;
		rep(j, D) {
			ll pre = (i + j) ? sum[i + j - 1] : 0;
			mm[pre]++;

			ll tmp = sum[i + j] - k;
			if (mm.count(tmp))
				cur += mm[tmp];

			ans[o][i + j] = cur;
		}
		for (int j = i + D; j < n; j++) {
			ll tmp = sum[j] - k;
			if (mm.count(tmp))
				cur += mm[tmp];
			ans[o][j] = cur;
		}
	}

	//cerr << clock() / (double) CLOCKS_PER_SEC << endl;

	int q;
	cin >> q;
	rep(i, q) {
		int l = nint() - 1;
		int r = nint() - 1;
		cout << getans(l, r) << "\n";
	}

	//cerr << clock() / (double) CLOCKS_PER_SEC << endl;
}









