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
const int MAX_NODE = MAX_N; // 10 * 1000 * 1000 + 5;

struct RND
{
	int x = 123456789;
	int y = 362436069;
	int z = 521288629;

	int my_rand()
	{
		//x ^= x << 16;
		//x ^= x >> 5;
		//x ^= x << 1;

		//unsigned int t = x;
		//x = y;
		//y = z;
		//z = t ^ x ^ y;

		//return z;
		return ((rand() << 15) ^ rand());
	}

	inline int next(int x)
	{
		return rand() % x;
	}

	inline int next(int a, int b)
	{
		return a + (rand() % (b - a));
	}

	inline double nextDouble()
	{
		return (rand() + 0.5) * (1.0 / 4294967296.0);
	}
};

static RND rnd;

/** Interface */

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x);
inline void writeChar(int x);
inline void writeWord(const char *s);
inline void flush();

/** Read */

static const int buf_size = 4096;

inline int getChar()
{
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar()
{
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt()
{
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x)
{
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

inline void flush()
{
	if (write_pos)
		fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}

template <class T>
inline void writeInt(T x)
{
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
}

inline void writeWord(const char *s)
{
	while (*s)
		writeChar(*s++);
}

struct node
{
	int value;
	int left;
	int right;
	int parent;
	int size;

	node()
	{
		value = 0;
		left = -1;
		right = -1;
		parent = -1;
		size = 1;
	}
	node(int _value)
	{
		value = _value;
		left = -1;
		right = -1;
		parent = -1;
		size = 1;
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

inline int new_node(int value)
{
	assert(cnt_nodes < MAX_NODE);

	nodes[cnt_nodes].value = value;
	nodes[cnt_nodes].size = 1;
	nodes[cnt_nodes].parent = -1;
	nodes[cnt_nodes].left = -1;
	nodes[cnt_nodes].right = -1;

	++cnt_nodes;

	return cnt_nodes - 1;
}

inline int get_size(int t)
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

inline void calc(int t)
{
	if (t != -1)
	{
		nodes[t].size = get_size(nodes[t].left) + get_size(nodes[t].right) + 1;
	}
}

void setParent(int child, int parent)
{
	if (child != -1)
	{
		nodes[child].parent = parent;
	}
}

void updateChilds(int parent)
{
	if (parent != -1)
	{
		setParent(nodes[parent].left, parent);
		setParent(nodes[parent].right, parent);
	}
}

void rotate(int child, int parent)
{
	int grandParent = nodes[parent].parent;
	if (grandParent != -1)
	{
		if (nodes[grandParent].left == parent)
		{
			nodes[grandParent].left = child;
		}
		if (nodes[grandParent].right == parent)
		{
			nodes[grandParent].right = child;
		}
	}
	if (nodes[parent].left == child)
	{
		nodes[parent].left = nodes[child].right;
		nodes[child].right = parent;
	}
	else
	{
		nodes[parent].right = nodes[child].left;
		nodes[child].left = parent;
	}

	updateChilds(child);
	updateChilds(parent);

	nodes[child].parent = grandParent;

	calc(parent);
	calc(child);
	calc(grandParent);
}

int splay(int v)
{
	if (v == -1) return -1;
	if (nodes[v].parent == -1) return v;

	int parent = nodes[v].parent;
	int grandParent = nodes[parent].parent;

	if (grandParent == -1)
	{
		rotate(v, parent);
		return v;
	}

	bool zigzig = false;
	if (nodes[grandParent].left == parent && nodes[parent].left == v) zigzig = true;
	if (nodes[grandParent].right == parent && nodes[parent].right == v) zigzig = true;
	if (zigzig)
	{
		rotate(parent, grandParent);
		rotate(v, parent);
	}
	else
	{
		rotate(v, parent);
		rotate(v, grandParent);
	}
	return splay(v);
}

int lowerBound(int x, int key)
{
	if (x == -1) return -1;

	if (nodes[x].value == key)
	{
		return splay(x);
	}

	if (nodes[x].value > key && nodes[x].left != -1)
	{
		return lowerBound(nodes[x].left, key);
	}

	if (nodes[x].value < key && nodes[x].right != -1)
	{
		return lowerBound(nodes[x].right, key);
	}

	return splay(x);
}

void split(int root, int &t1, int &t2, int key)
{
	if (root == -1)
	{
		t1 = t2 = -1;
	}

	root = lowerBound(root, key);
	if (nodes[root].value < key)
	{
		int right = nodes[root].right;
		setParent(nodes[root].right, -1);
		nodes[root].right = -1;

		t1 = root;
		t2 = right;
	}
	else
	{
		int left = nodes[root].left;
		setParent(nodes[root].left, -1);
		nodes[root].left = -1;

		t1 = left;
		t2 = root;
	}

	calc(t1);
	calc(t2);
}

int merge(int left, int right)
{
	if (left == -1) return right;
	if (right == -1) return left;

	right = lowerBound(right, nodes[left].value);

	nodes[right].left = left;
	updateChilds(right);
	calc(right);

	return right;
}

void print(int t)
{
	if (t != -1)
	{
		print(nodes[t].left);
		printf("%d ", nodes[t].value);
		print(nodes[t].right);
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
		tree[2 * v + 2].tree = t1;
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
		nodes[tree[v].tree].value = value;
		//nodes[tree[v].tree].y = rnd.my_rand();
		tree[v].max = value;
	}
	else
	{
		int t1, t2;
		split(tree[v].tree, t1, t2, tree[2 * v + 1].max + 1);
		tree[2 * v + 1].tree = t1;
		tree[2 * v + 2].tree = merge(tree[2 * v + 2].tree, t2);

		int m = ((l + r) >> 1);

		change_v(2 * v + 1, l, m, x, value);
		change_v(2 * v + 2, m, r, x, value);

		tree[v].max = max(tree[2 * v + 1].max, tree[2 * v + 2].max);

		split(tree[2 * v + 2].tree, t1, t2, tree[2 * v + 1].max + 1);
		tree[v].tree = merge(tree[2 * v + 1].tree, t2);
		tree[2 * v + 2].tree = t1;
	}
}

inline int get(int ptr)
{
	int t = tree[0].tree;

	if (get_size(t) < ptr)
	{
		return -1;
	}
	else
	{
		--ptr;
		while (ptr != get_size(nodes[t].left))
		{
			if (get_size(nodes[t].left) > ptr)
			{
				t = nodes[t].left;
			}
			else
			{
				ptr -= get_size(nodes[t].left) + 1;
				t = nodes[t].right;
			}
		}

		return nodes[t].value;
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	//scanf("%d%d", &n, &q);
	n = readInt();
	q = readInt();

	for (int i = 0; i < n; ++i)
	{
		//scanf("%d", &arr[i]);
		arr[i] = readInt();
	}

	build(0, 0, n);

	//print(tree[0].tree);
	//printf("\n");

	int type, at, value;
	for (int i = 0; i < q; ++i)
	{
		//scanf("%d", &type);
		type = readInt();
		if (type == 1)
		{
			//scanf("%d%d", &at, &value);
			at = readInt();
			value = readInt();
			change_v(0, 0, n, at - 1, value);
		}
		else
		{
			//scanf("%d", &value);
			value = readInt();
			//printf("%d\n", get(value));
			writeInt(get(value));
			writeChar('\n');
		}
	}

	flush();

	fclose(stdin);
	fclose(stdout);

	return 0;
}
