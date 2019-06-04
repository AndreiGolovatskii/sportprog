#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int VN = 1e5 + 2;

char t[int(1e6) + 1], s[30 + 1];
int root = 1, vn = 2, End[VN], Next[VN][26];
int n, is[VN];

void add( int i, const char *s ) {
	int v = root;
	while (*s) {
		int &r = Next[v][*s++ - 'a'];
		if (!r)
			r = vn++;
		v = r;
	}
	End[v] = i;
}

int main() {
	scanf("%s%d ", t, &n);
	fill(End, End + VN, n);
	forn(i, n)
		scanf("%s", s), add(i, s);
	for (int i = 0; t[i]; i++)
		for (int v = root, j = i; v && t[j]; j++)
			v = Next[v][t[j] - 'a'], is[End[v]] = 1;
	forn(i, n)
		puts(is[i] ? "Yes" : "No");
}
