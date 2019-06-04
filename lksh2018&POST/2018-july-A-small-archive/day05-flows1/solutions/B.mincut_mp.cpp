#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int max_m = 20000;
const int max_n = 500;
const long long inf = (long long) 1e18;
char tmp[max_n];
vector < int > best;
bool used[max_n];

struct edge
{
	int toV, next, c, f;
};

int freeE, start[max_n], n, q[max_n], d[max_n], s, t, ptr[max_n];
edge r[max_m];

void simple_add(int u, int v, int c)
{
	r[freeE].toV = v, r[freeE].next = start[u], r[freeE].c = c, r[freeE].f = 0, start[u] = freeE, freeE++;
}

void add(int u, int v, int c)
{
	simple_add(u, v, c), simple_add(v, u, 0);
}

void bfs()
{
	int qh = 0, qe = 1;
	for (int i = 0; i < n; ++i)
		d[i] = n + 1;
	q[0] = s, d[s] = 0;
	while (qh < qe)
	{
		int u = q[qh++];
		for (int j = start[u]; j != -1; j = r[j].next)
			if ((d[r[j].toV] > d[u] + 1) && (r[j].c - r[j].f > 0))
				d[r[j].toV] = d[u] + 1, q[qe++] = r[j].toV;
	}
	for (int i = 0; i < n; ++i)
		ptr[i] = start[i];
}

long long dfs(int v, long long mx)
{
	if ((v == t) || (mx == 0))
		return mx;
	long long res = 0;
	for ( ; (mx > 0) && (ptr[v] != -1); ptr[v] = r[ptr[v]].next)
	{
		if (d[r[ptr[v]].toV] != d[v] + 1) 
			continue;
		long long tmp = dfs(r[ptr[v]].toV, min(mx, 0ll + r[ptr[v]].c - r[ptr[v]].f));
		if (tmp > 0)
		{
			r[ptr[v]].f += tmp;
			r[ptr[v] ^ 1].f -= tmp;
			mx -= tmp;
			res += tmp;
			if (mx == 0)
				return res;
		}
	}
	return res;
}

void get_dfs(int v)
{
	if (used[v]) 
		return;
	best.push_back(v);
	used[v] = true;
	for (int j = start[v]; j != -1; j = r[j].next)
		if (r[j].c - r[j].f > 0)
			get_dfs(r[j].toV);
}

void get_cut()
{
	best.clear();
	memset(used, 0, sizeof(used));
	get_dfs(0);
}

int main()
{
	scanf("%d", &n);
	memset(start, -1, sizeof(start));
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", tmp);
		for (int j = 0; j < n; ++j)
			if (tmp[j] == '1')
				add(i, j, 1);
	}
	s = 0;
	long long minf = inf;
	for (t = 1; t < n; ++t)
	{
		for (int i = 0; i < freeE; ++i)
			r[i].f = 0;
		long long f = 0;
		for (int i = 0; i < n; ++i)
		{
			bfs();
			f += dfs(s, inf);
		}
		if (f < minf)
			get_cut(), minf = f;
	}
	memset(used, 0, sizeof(used));
	for (int i = 0; i < (int)best.size(); ++i)
		printf("%d ", best[i] + 1), used[best[i]] = true;
	printf("\n");
	for (int i = 0; i < n; ++i)
		if (!used[i])
			printf("%d ", i + 1);
	printf("\n");
	return 0;
}