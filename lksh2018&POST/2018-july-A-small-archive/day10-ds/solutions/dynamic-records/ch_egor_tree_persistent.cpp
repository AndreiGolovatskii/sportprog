#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <bitset>

#pragma comment(linker, "/STACK:256000000")

using namespace std;

typedef long long int int64;
typedef long double double80;

const int INF = (1 << 29) + 5;
const int64 LLINF = (1ll << 59) + 5;
const int MOD = 1000 * 1000 * 1000 + 7;
const int MAX_N = 5000 * 100 + 5;
const int MAX_NODE = 60 * 1000 * 1000 + 5;

struct node
{
	int value;
	int size;
	int l;
	int r;

	node()
	{
		value = 0;
		size = 1;
		l = -1;
		r = -1;
	}

	node(int _value)
	{
		value = _value;
		size = 1;
		l = -1;
		r = -1;
	}
};

struct tree_node
{
	int tree;
	int max;
};

int n, q;
int arr[MAX_N];
tree_node tree[4 * MAX_N];
node nodes[MAX_NODE];
int cnt_nodes = 0;

int new_node(int value)
{
	assert(cnt_nodes < MAX_NODE);

	nodes[cnt_nodes].value = value;
	nodes[cnt_nodes].size = 1;
	nodes[cnt_nodes].l = -1;
	nodes[cnt_nodes].r = -1;

	++cnt_nodes;

	return cnt_nodes - 1;
}

int clone(int t)
{
	assert(cnt_nodes < MAX_NODE);

	nodes[cnt_nodes].value = nodes[t].value;
	nodes[cnt_nodes].size = nodes[t].size;
	nodes[cnt_nodes].l = nodes[t].l;
	nodes[cnt_nodes].r = nodes[t].r;

	++cnt_nodes;

	return cnt_nodes - 1;
}

int get_size(int t)
{
	if (t == -1)
	{
		return 0;
	}
	else
	{
		return nodes[t].size;
	}
}

void calc(int t)
{
	if (t != -1)
	{
		nodes[t].size = 1 + get_size(nodes[t].l) + get_size(nodes[t].r);
	}
}


int merge(int t1, int t2)
{
	if (t1 == -1)
	{
		return t2;
	}
	else if (t2 == -1)
	{
		return t1;
	}
	else
	{
		int new_t;

		if (1ll * get_size(t1) * RAND_MAX  > 1ll * rand() * (get_size(t1) + get_size(t2)))
		{
			new_t = clone(t1);
			nodes[new_t].r = merge(nodes[new_t].r, t2);
		}
		else
		{
			new_t = clone(t2);
			nodes[new_t].l = merge(t1, nodes[new_t].l);
		}

		calc(new_t);
		return new_t;
	}
}

void split(int t, int &t1, int &t2, int x)
{
	if (t == -1)
	{
		t1 = -1;
		t2 = -1;
	}
	else
	{
		int new_t = clone(t);

		if (nodes[new_t].value < x)
		{
			split(nodes[new_t].r, nodes[new_t].r, t2, x);
			t1 = new_t;
		}
		else
		{
			split(nodes[new_t].l, t1, nodes[new_t].l, x);
			t2 = new_t;
		}

		calc(new_t);
	}
}

void print(int t)
{
	if (t != -1)
	{
		print(nodes[t].l);
		printf("%d ", nodes[t].value);
		print(nodes[t].r);
	}
}

void build(int v, int l, int r)
{
	if (r - l == 1)
	{
		tree[v].tree = new_node(arr[l]);
		tree[v].max = arr[l];
	}
	else
	{
		int m = ((l + r) >> 1);

		build(2 * v + 1, l, m);
		build(2 * v + 2, m, r);

		tree[v].max = max(tree[2 * v + 1].max, tree[2 * v + 2].max);
		
		int t1, t2;
		split(tree[2 * v + 2].tree, t1, t2, tree[2 * v + 1].max + 1);
		tree[v].tree = merge(tree[2 * v + 1].tree, t2);
	}
}

void change_v(int v, int l, int r, int x, int value)
{
	if (x < l || r <= x)
	{
		return;
	}
	else if (r - l == 1)
	{
		tree[v].tree = new_node(value);
		tree[v].max = value;
	}
	else
	{
		int m = ((l + r) >> 1);

		change_v(2 * v + 1, l, m, x, value);
		change_v(2 * v + 2, m, r, x, value);

		tree[v].max = max(tree[2 * v + 1].max, tree[2 * v + 2].max);

		int t1, t2;
		split(tree[2 * v + 2].tree, t1, t2, tree[2 * v + 1].max + 1);
		tree[v].tree = merge(tree[2 * v + 1].tree, t2);
	}
}

int get(int ptr)
{
	int t = tree[0].tree;
	
	if (get_size(t) < ptr)
	{
		return -1;
	}
	else
	{
		--ptr;
		while (ptr != get_size(nodes[t].l))
		{
			if (get_size(nodes[t].l) > ptr)
			{
				t = nodes[t].l;
			}
			else
			{
				ptr -= get_size(nodes[t].l) + 1;
				t = nodes[t].r;
			}
		}

		return nodes[t].value;
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
	}

	build(0, 0, n);

	int type, at, value;
	for (int i = 0; i < q; ++i)
	{
		scanf("%d", &type);
		if (type == 1)
		{
			scanf("%d%d", &at, &value);
			change_v(0, 0, n, at - 1, value);
		}
		else
		{
			scanf("%d", &value);
			printf("%d\n", get(value));
		}
	}

	fclose(stdin);
	fclose(stdout);

	return 0;
}
