/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

int main() {
	struct Query {
		int type, x;
	};
	int n = readInt();
	vector<vector<int>> g(n + 1);
	vector<Query> op(n + 1);
	op[0].type = 0;
	for (int i = 1; i <= n; i++) {
		op[i].type = readInt();
		int p = readInt();
		g[p].push_back(i);
		if (op[i].type == 1)
			op[i].x = readInt();
	}
	int st = 0, en = 0;
	vector<int> q(n), ans(n + 1);
	function<void(int)> dfs = [&]( int v ) {
		if (op[v].type == 1)
			q[en++] = op[v].x;
		else if (op[v].type == -1)
			ans[v] = q[st++];
		for (int i : g[v])
			dfs(i);
		if (op[v].type == 1)
			en--;
		else if (op[v].type == -1)
			st--;
	};
	dfs(0);
	for (int i = 1; i <= n; i++) 
		if (op[i].type == -1)
			writeInt(ans[i], '\n');
}
