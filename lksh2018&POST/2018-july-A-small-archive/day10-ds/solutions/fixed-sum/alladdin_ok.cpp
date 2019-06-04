/*AMETHYSTS*/
#pragma comment(linker, "/STACK:1000000000")
#include <cstdio>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <bitset>
#include <deque>
#include <stack>
#include <climits>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <cassert>

#define ll long long
#define ld double
#define pii pair <ll, ll>
#define mp make_pair

using namespace std;

const double PI = 3.14159265358979323846;
const ll maxn = (ll)400001;
const ll mod = (ll)1e9 + 7;
const ll inf = (ll)1e9 + 7;
const double eps = 1e-9;

int n, k, l, r, q, t[maxn], a[maxn], sz;
vector<vector<pair<int, pair<int, int> > > > v(maxn);
ll sum[maxn], tsum[maxn], p[maxn], p1[maxn], tans, ans[maxn], cnt[maxn];
map<ll, int> m;

void add(int pos, bool fl) {
	if (fl) {
		tans += cnt[p[pos]];
	}
	else {
		tans += cnt[p1[pos]];
	}
	cnt[tsum[pos]]++;
}

void del(int pos, bool fl) {
	cnt[tsum[pos]]--;
	if (fl) {
		tans -= cnt[p[pos]];
	}
	else {
		tans -= cnt[p1[pos]];
	}
}

int main() {
	
	scanf("%d %d", &n, &k);
	sz = (int)sqrt((ld)n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &l, &r);
		l--;
		v[l / sz].push_back(mp(r, mp(l, i)));
	}
	for (int i = 1; i <= n; i++) {
		if (t[i] == 1) {
			sum[i] = sum[i - 1] + a[i];
		}
		else {
			sum[i] = sum[i - 1] - a[i];
		}
	}
	int it = 0;
	for (int i = 0; i <= n; i++) {
		if (!m.count(sum[i])) {
			m[sum[i]] = it++;
		}
		if (!m.count(sum[i] + k)) {
			m[sum[i] + k] = it++;
		}
		if (!m.count(sum[i] - k)) {
			m[sum[i] - k] = it++;
		}
		tsum[i] = m[sum[i]];
		p[i] = m[sum[i] - k];
		p1[i] = m[sum[i] + k];
	}
	for (int bl = 0; bl <= n / sz + 10; bl++) {
		sort(v[bl].begin(), v[bl].end());
		int cr = bl * sz;
		int cl = bl * sz;
		tans = 0;
		memset(cnt, 0, sizeof cnt);
		tans = 0;
		for (int i = 0; i < v[bl].size(); i++) {
			while (cr <= v[bl][i].first) {
				add(cr, true);
				cr++;
			}
			while (cl < v[bl][i].second.first) {
				del(cl, false);
				cl++;
			}
			while (cl > v[bl][i].second.first) {
				cl--;
				add(cl, false);
			}
			while (cr > v[bl][i].first + 1) {
				del(cr - 1, true);
				cr--;
			}
			ans[v[bl][i].second.second] = tans;
		}
	}
	for (int i = 0; i < q; i++) {
		printf("%I64d\n", ans[i]);
	}
	return 0;
}