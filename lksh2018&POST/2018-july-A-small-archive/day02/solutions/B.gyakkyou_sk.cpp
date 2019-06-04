/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cstdio>
#include <cassert>
#include <iostream>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()

typedef long long ll;

const int Q = 450000, D = 30, TN = Q * (D + 1) + 1;
struct node {
	int l, r, sum;
} t[TN]; 
int tpos = 1;

int newNode( int l, int r, int add ) {
	t[tpos] = {l, r, add + t[l].sum + t[r].sum};
	return tpos++;
}

int change( int i, int dx, int v, int vl = 0, int vr = 1 << D ) {
    assert(vl <= i && i < vr);
	if (vr - vl == 1)
		return newNode(0, 0, dx + t[v].sum);
	int vm = (vl + vr) / 2;
	int l = v ? t[v].l : 0, r = v ? t[v].r : 0;
	if (i < vm)
		return newNode(change(i, dx, l, vl, vm), r, 0);
	return newNode(l, change(i, dx, r, vm, vr), 0);
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int a, q, n, l, m, mod = 1e9;
	cin >> n >> a >> l >> m;
	int roots[n + 1] = {0};
	forn(i, n)
		roots[i + 1] = change(a, 1, roots[i]), a = ((ll)a * l + m) % mod;

	auto get = [&]( int l, int r, int k ) {
		l = roots[l], r = roots[r + 1];
		int res = 0, tmp;
		forn(i, D)
			if ((tmp = t[t[r].l].sum - t[t[l].l].sum) > k)
				l = t[l].l, r = t[r].l;
			else
				l = t[l].r, r = t[r].r, res += 1 << (D - i - 1), k -= tmp;
		return res;
	};

	long long res = 0;
	cin >> q;
	while (q--) {
		int num, x, lx, mx, y, ly, my, k, lk, mk;
		cin >> num >> x >> lx >> mx >> y >> ly >> my >> k >> lk >> mk;
		x--, y--, k--;
		while (num--) {
			int i = min(x, y), j = max(x, y);
			res += get(i, j, k);
			x = ((ll)i * lx + mx) % n;
			y = ((ll)j * ly + my) % n;
			k = ((ll)k * lk + mk) % (max(x, y) - min(x, y) + 1);
		}
	}
	cout << res << endl;
}
