#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef long long ll;
typedef double dbl;

struct pnt
{
	int x, y;

	pnt operator - ( pnt p ) { return {x - p.x, y - p.y}; }
	pnt operator + ( pnt p ) { return {x + p.x, y + p.y}; }
	ll operator * ( pnt p ) { return (ll)x * p.y - (ll)y * p.x; }

	bool operator == ( pnt p ) { return x == p.x && y == p.y; }

	ll d2() { return (ll)x * x + (ll)y * y; }
	dbl d() { return sqrt(d2()); }

	void read() { scanf("%d%d", &x, &y); }
};

#define maxn 40

int W, H, n;
pnt st[3], en;
pnt p[maxn][4];

int tn;
pnt tp[10];

int sgn( ll x )
{
	return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

int Intr( pnt a, pnt b, pnt c, pnt d )
{
	return
		sgn((a - c) * (d - c)) * sgn((b - c) * (d - c)) == -1 &&
		sgn((c - a) * (b - a)) * sgn((d - a) * (b - a)) == -1;
}

int IsIn( pnt a, pnt b, pnt p )
{
	return (p - a) * (p - b) == 0 &&
		min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
		min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

int IsIn( int an, pnt *a, pnt t )
{
	int cnt = 0;
	forn(i, an)
	{
		pnt p = a[i], q = a[i + 1];
		if (p.y > q.y)
			swap(p, q);
		if (p.y < t.y && t.y <= q.y)
			cnt += ((t - p) * (q - p) > 0);
	}
	return cnt & 1;
}

int IsIntr( int an, pnt *a, int bn, pnt *b )
{
	int ax1 = a[0].x, ax2 = a[0].x, ay1 = a[0].y, ay2 = a[0].y;
	for (int i = 1; i < an; i++)
	{
		ax1 = min(ax1, a[i].x), ax2 = max(ax2, a[i].x);
		ay1 = min(ay1, a[i].y), ay2 = max(ay2, a[i].y);
	}
	int bx1 = b[0].x, bx2 = b[0].x, by1 = b[0].y, by2 = b[0].y;
	for (int i = 1; i < bn; i++)
	{
		bx1 = min(bx1, b[i].x), bx2 = max(bx2, b[i].x);
		by1 = min(by1, b[i].y), by2 = max(by2, b[i].y);
	}
	if (ay1 >= by2 || by1 >= ay2 || ax1 >= bx2 || bx1 >= ax2)
		return 0;		
	
	forn(j, bn)
		forn(i, an)
			if (Intr(a[i], a[i + 1], b[j], b[j + 1]))
				return 1;

	tn = 0;
	forn(j, bn)
		forn(i, an)
			if (IsIn(a[i], a[i + 1], b[j]))
				tp[tn++] = b[j], i = an;

	forn(i, an)
	{
		int f = 0;
		forn(j, bn)
			if (IsIn(b[j], b[j + 1], a[i]))
				tp[tn++] = a[i], j = bn, f = 1;
		if (!f && IsIn(bn, b, a[i]))
			return 1;
	}

	int x = 0;
	forn(i, tn)
		if (!(tp[i] == tp[0]))
			x = i;
	forn(i, tn)
		if ((tp[0] - tp[i]) * (tp[x] - tp[i]) != 0)
			return 1;
	return 0;
}

int Check( int an, pnt *a )
{
	forn(i, an)
		if (!(0 <= a[i].x && a[i].x <= W && 0 <= a[i].y && a[i].y <= H))
			return 0;
	forn(i, n)
		if (IsIntr(3, p[i], an, a))
			return 0;
	return 1;
}

int CheckPos( pnt p )
{
	pnt x[4];
	forn(i, 3)
		x[i] = p + st[i] - st[0];
	x[3] = x[0];
	return Check(3, x);
}

bool pless( pnt a, pnt b )
{
	return a * b ? a * b > 0 : a.d2() < b.d2();
}

int CheckE( pnt p1, pnt p2 )
{
	if (p1 == p2)
		return 1;

	int k = 0;
	pnt p[6];
	forn(i, 3)
		p[k++] = p1 + st[i] - st[0];
	forn(i, 3)
		p[k++] = p2 + st[i] - st[0];

	int mi = 0;
	#define F(i) mp(p[i].y, -p[i].x)
	forn(i, k)
		if (F(i) < F(mi))
			mi = i;
	swap(p[0], p[mi]);
	for (int i = 1; i < k; i++)
		p[i] = p[i] - p[0];
	sort(p + 1, p + k, pless);

	int sp = 0;
	pnt ss[6];
	ss[sp++] = {0, 0};
	for (int i = 1; i < k; i++)
	{
		while (sp >= 2 && (ss[sp - 1] - ss[sp - 2]) * (p[i] - ss[sp - 1]) <= 0)
			sp--;
		ss[sp++] = p[i];
	}
	forn(i, sp)
		ss[i] = ss[i] + p[0];
	ss[sp] = ss[0];
	return Check(sp, ss);
}	

#define maxv 370

int stV, enV;
int vn = 0;
pnt v[maxv];

char c[maxv][maxv];
int u[maxv];
dbl d[maxv];

int main()
{
	scanf("%d%d", &W, &H);
	forn(i, 3)
		st[i].read();
	en.read();
	scanf("%d", &n);
	forn(i, n)
		forn(j, 3)
			p[i][j].read();
	forn(i, n)
		p[i][3] = p[i][0];

	if (!CheckPos(st[0]) || !CheckPos(en))
	{
		puts("-1");
		return 0;
	}

	stV = vn, v[vn++] = st[0];
	enV = vn, v[vn++] = en;
	forn(i, n)
		forn(j, 3)
			forn(k, 3)
			{
				pnt tmp = p[i][j] - st[k] + st[0];
				if (CheckPos(tmp))
					v[vn++] = tmp;
			}
	memset(c, -1, sizeof(c));

	forn(i, vn)
		d[i] = 1e100, u[i] = 0;
	d[stV] = 0;
	int mi = stV;
	while (mi != -1)
	{
		dbl tmp;
		u[mi] = 1;
		forn(i, vn)
			if (!u[i] && d[i] > (tmp = d[mi] + (v[mi] - v[i]).d()) && tmp + (v[i] - v[enV]).d() + 1e-6 < d[enV])
			{
				if (c[mi][i] == -1)
					c[mi][i] = c[i][mi] = CheckE(v[mi], v[i]);
				if (c[mi][i])
					d[i] = tmp;
			}
		mi = -1;
		forn(i, vn)
			if (!u[i] && (mi == -1 || d[mi] > d[i]))
				mi = i;
	}
	if (d[enV] > 1e20)
		puts("-1");
	else
		printf("%.3f\n", d[enV]);
}
