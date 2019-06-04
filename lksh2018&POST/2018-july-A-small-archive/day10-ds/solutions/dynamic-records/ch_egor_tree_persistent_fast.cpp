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
const int MAX_N = 500 * 1000 + 5;
const int MAX_NODE = 64 * 1000 * 1000 + 5;
const int WARNING_CNT_NODES = 63 * 1000 * 1000 + 5;

struct RND
{
	unsigned int x = 123456789;
	unsigned int y = 362436069;
	unsigned int z = 521288629;
	unsigned int MAX_RAND = 4294967295ll;

	unsigned int my_rand()
	{
		x ^= x << 16;
		x ^= x >> 5;
		x ^= x << 1;

		unsigned int t = x;
		x = y;
		y = z;
		z = t ^ x ^ y;

		return z;
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

inline int new_node(int value)
{
	assert(cnt_nodes < MAX_NODE);

	nodes[cnt_nodes].value = value;
	nodes[cnt_nodes].size = 1;
	nodes[cnt_nodes].l = -1;
	nodes[cnt_nodes].r = -1;

	++cnt_nodes;

	return cnt_nodes - 1;
}

inline int clone(int t)
{
	assert(cnt_nodes < MAX_NODE);

	nodes[cnt_nodes].value = nodes[t].value;
	nodes[cnt_nodes].size = nodes[t].size;
	nodes[cnt_nodes].l = nodes[t].l;
	nodes[cnt_nodes].r = nodes[t].r;

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

		if (1ll * get_size(t1) * rnd.MAX_RAND  > 1ll * rnd.my_rand() * (get_size(t1) + get_size(t2)))
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

	//scanf("%d%d", &n, &q);
	n = readInt();
	q = readInt();

	for (int i = 0; i < n; ++i)
	{
		//scanf("%d", &arr[i]);
		arr[i] = readInt();
	}

	build(0, 0, n);

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
			arr[at - 1] = value;
		}
		else
		{
			//scanf("%d", &value);
			value = readInt();
			//printf("%d\n", get(value));
			writeInt(get(value));
			writeChar('\n');
		}

		if (cnt_nodes > WARNING_CNT_NODES)
		{
			cnt_nodes = 0;
			build(0, 0, n);
		}
	}

	flush();

	fclose(stdin);
	fclose(stdout);

	return 0;
}
