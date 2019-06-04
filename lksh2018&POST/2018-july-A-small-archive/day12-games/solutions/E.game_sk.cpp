/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

struct Graph {
	vector<vector<int>> c;
	vector<int> used, pair, mark;
	int cc, n1, n2;

	Graph( int n1, int n2 ) : c(n1), used(n1, 0), pair(n2, -1), mark(n1, 0), cc(1), n1(n1), n2(n2) { }

	bool dfs( int v ) {
		used[v] = cc;
		for (int x : c[v]) {
			int &p = pair[x];
			if (p == -1 || (p != -2 && used[p] != cc && dfs(p))) {
				p = v;
				return 1;
			}
		}
		return 0;
	}
	void matching() {
		forn(i, n1)
			if (dfs(i))
				cc++;
		vector<int> pair_copy(pair);
		forn(i, n2)
			if (pair[i] != -1)
				mark[pair[i]] = 1;
		forn(j, n2) {
			bool result = (pair_copy[j] == -1);
			if (!result) {
				copy(pair_copy.begin(), pair_copy.end(), pair.begin());
				cc++, pair[j] = -2;
				forn(i, n1)
					if ((!mark[i] || i == pair_copy[j]) && used[i] != cc && dfs(i))
						result = 1, i = n1;
			}
			putchar("NP"[result]);
		}
		puts("");
	}
};

int main() {
	int n1 = readInt();
	int n2 = readInt();
	int m = readInt();
	Graph g1(n1, n2), g2(n2, n1);
	while (m--) {
		int a = readInt() - 1;
		int b = readInt() - 1;
		g1.c[a].push_back(b);
		g2.c[b].push_back(a);
	}
	forn(t, 2) {
		swap(g1, g2);
		g1.matching();
	}
}
