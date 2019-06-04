/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()

struct Event {
	int x, i;
	bool operator < ( Event e ) const { return x < e.x; }
};

struct Node {
	Node *l, *r;
	int x;
	Node( Node *l, Node *r, int x ) : l(l), r(r), x(x) { }
};

#define get(v, x) (v ? v->x : 0)

// [l, r)
Node *change( Node *root, int l, int r, int i, int x ) {
	if (i < l || r <= i)
		return root;
	if (r - l == 1)
		return new Node(0, 0, x);
	int m = (l + r) / 2;
	Node *vl = change(get(root, l), l, m, i, x);
	Node *vr = change(get(root, r), m, r, i, x);
	return new Node(vl, vr, min(get(vl, x), get(vr, x)));
}

int value( Node *v, int l, int r, int i ) {
	if (!v)
		return 0;
	if (r - l == 1)
		return v->x;
	int m = (l + r) / 2;
	if (i < m)
		return value(v->l, l, m, i);
	else	
		return value(v->r, m, r, i);
}

int main() {
    readInt(); // n is unused
    int maxS = readInt();
    int m = readInt();
    vector<Event> es(2 * m);
    forn(i, m) {
    	int c = readInt() - 1;
    	int a = readInt();
    	int b = readInt();
    	es[2 * i + 0] = {a, c};
    	es[2 * i + 1] = {b, c};
    }
    sort(all(es));
	fprintf(stderr, "time = %.2f : read, sorted\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
    
    Node *root = 0;
    vector<pair<int, Node*>> roots;
    for (auto e : es) {
    	roots.push_back(make_pair(e.x, root));
    	int cur = value(root, 0, maxS + 1, e.i);
    	root = change(root, 0, maxS + 1, e.i, cur == INT_MAX ? e.x : INT_MAX);
    }
   	roots.push_back(make_pair(INT_MAX, root));
	fprintf(stderr, "time = %.2f : built\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
	
    int q = readInt(), p = 0;
    while (q--) {
    	int a = readInt() + p;
    	int b = readInt() + p;
    	root = lower_bound(all(roots), make_pair(b, (Node *)0))->second;
    	int l = 0, r = maxS + 1;
    	while (root && r - l > 1) {
    		int m = (l + r) / 2;
    		if (get(root->l, x) > a)
    			root = root->r, l = m;
    		else
    			root = root->l, r = m;
    	}
    	p = (l == maxS ? 0 : l + 1);
    	writeInt(p, '\n');
    }
	fprintf(stderr, "time = %.2f : finish\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
}
