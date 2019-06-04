#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; i++)

typedef long long ll;

const int maxN = 250000;

int n0, T;
int n, num[maxN + 1];
char s[maxN + 1];
int p[maxN], col[maxN], p2[maxN], len[maxN];

void BuildArray() {
	int ma = max(n, 256);
	forn(i, n)
		col[i] = s[i], p[i] = i;

	for (int k2 = 1; k2 / 2 < n; k2 *= 2) {
		int k = k2 / 2;
		memset(num, 0, sizeof(num));
		forn(i, n)
			num[col[i] + 1]++;
		forn(i, ma)
			num[i + 1] += num[i];
		forn(i, n)
			p2[num[col[(p[i] - k + n) % n]]++] = (p[i] - k + n) % n;

		int cc = 0;
		forn(i, n) {
			if (i && (col[p2[i]] != col[p2[i - 1]] || col[(p2[i] + k) % n] != col[(p2[i - 1] + k) % n]))
				cc++;
			num[p2[i]] = cc;
		}
		forn(i, n)
			p[i] = p2[i], col[i] = num[i];
	}
	forn(i, n)
		p2[p[i]] = i;
}

void BuildLCP() {
	int lcp = 0;
	forn(i, n) {
		int j = p2[i];
		lcp = max(0, lcp - 1);
		if (j != n - 1)
			while (lcp < n && s[(p[j] + lcp) % n] == s[(p[j + 1] + lcp) % n])
				lcp++;
		len[j] = lcp;
	}
}

void FindPeriod()
{
	int k = 0;
	p[0] = 0;
	for (int i = 1; i < n; i++)
	{
		while (k && s[k] != s[i])
			k = p[k - 1];
		if (s[k] == s[i])
			k++;
		p[i] = k;
	}
	T = n;
	if (n % (n - p[n - 1]) == 0)
		n = T = n - p[n - 1];
}

int main()
{
	scanf("%d%s", &n, s), n0 = n;

	FindPeriod();
	BuildArray();
	BuildLCP();

	// res = sum of all LCP[i,i+1]
	ll res = (ll)(n0 - T) * n0;
	forn(i, n)
		res += len[i];
	printf("%.3f\n", (double)res / (n0 - 1));
	return 0;
}
