#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

struct point {
	ll x, y;
	point(ll x = 0, ll y = 0): x(x), y(y) {}
	ll operator*(point a) {
		return x * a.y - y * a.x;
	}
	ll operator^(point a) {
		return x * a.x + y * a.y;
	}
	point operator+(point a) {
		return point(x + a.x, y + a.y);
	}
	point operator-(point a) {
		return point(x - a.x, y - a.y);
	}
};

const int MAXN = 120000;

int n, k;
point pl[MAXN];
point pp[MAXN];
vector<point> mm1[MAXN];
vector<point> mm2[MAXN];
vector<pair<int, int> > vv;
point gl;

bool cmp(point a, point b) {
	if (gl * a >= 0 && gl * b < 0)
		return 1;
	if (gl * a < 0 && gl * b >= 0)
		return 0;
	if (gl * a == 0 && gl * b == 0) {
		if ((gl ^ a) > 0 && (gl ^ b) < 0)
			return 1;
		else
			return 0;
	}
	return a * b > 0;
}

int main() {
	k = readInt();
	n = readInt();
	for (int i = 0; i < k; ++i) {
		pl[i].x = readInt();
		pl[i].y = readInt();
	}
	pl[k] = pl[0];
	for (int i = 0; i < n; ++i) {
		pp[i].x = readInt();
		pp[i].y = readInt();
	}
	for (int i = 0; i < n; ++i) {
		int l = 0;
		int r = k - 1;
		int p1 = 0, p2 = 0;
		point p = pl[0] - pp[i];
		if (p * (pl[1] - pp[i]) >= 0) {
			while (r - l > 1) {
				int mid = (l + r) >> 1;
				if (p * (pl[mid] - pp[i]) >= 0)
					l = mid;
				else
					r = mid;
			}
			int tl = -1;
			int tr = l;
			while (tr - tl > 1) {
				int mid = (tl + tr) >> 1;
				if ((pl[mid] - pp[i]) * (pl[mid + 1] - pp[i]) > 0)
					tl = mid;
				else
					tr = mid;
			}
			p1 = tr;
			if ((pl[p1] - pp[i]) * (pl[k - 1] - pp[i]) > 0)
				p1 = k - 1;
			tl = l;
			tr = k - 1;
			while (tr - tl > 1) {
				int mid = (tl + tr) >> 1;
				if ((pl[mid] - pp[i]) * (pl[mid + 1] - pp[i]) <= 0)
					tl = mid;
				else
					tr = mid;
			}
			p2 = tr;
			if ((pl[p2] - pp[i]) * (pl[0] - pp[i]) <= 0)
				p2 = 0;
		}
		else {
			while (r - l > 1) {
				int mid = (l + r) >> 1;
				if (p * (pl[mid] - pp[i]) <= 0)
					l = mid;
				else
					r = mid;
			}
			int tl = -1;
			int tr = l;
			while (tr - tl > 1) {
				int mid = (tl + tr) >> 1;
				if ((pl[mid] - pp[i]) * (pl[mid + 1] - pp[i]) <= 0)
					tl = mid;
				else
					tr = mid;
			}
			p2 = tr;
			if ((pl[p2] - pp[i]) * (pl[k - 1] - pp[i]) <= 0)
				p2 = k - 1;
			tl = l;
			tr = k - 1;
			while (tr - tl > 1) {
				int mid = (tl + tr) >> 1;
				if ((pl[mid] - pp[i]) * (pl[mid + 1] - pp[i]) > 0)
					tl = mid;
				else
					tr = mid;
			}
			p1 = tr;
			if ((pl[p1] - pp[i]) * (pl[0] - pp[i]) > 0)
				p1 = 0;
		}
		point pd = pl[p1] - pp[i];
		mm1[p1].push_back(pd);
		pd = pl[p2] - pp[i];
		mm2[p2].push_back(pd);
		vv.push_back(make_pair(p1, p2));
	}
	ll ans = 0;
	for (int i = 0; i < k; ++i) {
		if (i == 0)
			gl = pl[k - 1] - pl[0];
		else
			gl = pl[i - 1] - pl[i];
		sort(mm2[i].begin(), mm2[i].end(), cmp);
		sort(mm1[i].begin(), mm1[i].end(), cmp);
		int now = 0;
		for (int j = 0; j < mm2[i].size(); ++j) {
			while (now < mm1[i].size() && (mm2[i][j] * mm1[i][now]) >= 0)
				++now;
			ans += now;
		}
	}
	ll cnt = 0;
	for (int i = 0; i < vv.size(); ++i) {
		if (vv[i].first >= vv[i].second) {
			if (vv[i].second > 0) {
				vv.push_back(make_pair(0, vv[i].second));
				++cnt;
			}
			vv[i].second = k;
		}
	}
	sort(vv.begin(), vv.end());
	for (int i = 0; i < vv.size(); ++i) {
		int x = lower_bound(vv.begin(), vv.end(), make_pair(vv[i].second, 0)) - vv.begin();
		ans += x - i - 1;
	}
	ans -= cnt * (cnt - 1) / 2;
	cout << ans << "\n";
}
