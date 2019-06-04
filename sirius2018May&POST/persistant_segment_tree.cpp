#include <bits/stdc++.h>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>

struct node{
    int l, r, v;
    node *cl, *cr;
    node(int l, int r, int v): l(l), r(r), v(v){}
};
node *build(int l, int r){
    node *root = new node(l, r, 0);
    if(l == r) {
        return root;
    } else {
        root->cl = build(l, (l + r) / 2);
        root->cr = build((l + r) / 2 + 1, r);
        root->v = root->cl->v + root->cr->v;
        return root;
    }
}



node *ch(node *root, int pos, int nv) {
    if(pos < root->l || pos > root->r) {
        return root;
    }
    if(root->l == root->r){
        node *nroot = new node(root->l, root->r, nv);
        return nroot;
    }
    node *nroot = new node(root->l, root->r, nv);
    nroot->cl = ch(root->cl, pos, nv);
    nroot->cr = ch(root->cr, pos, nv);
    nroot->v = nroot->cl->v + nroot->cr->v;
    return nroot;
}
const int MN = 5000 + 10;
node* ver[MN];
int que(int i, int j, int k) {
    node *l = ver[i - 1], *r = ver[j];
    while(l->l != l->r) {
        int lval = r->cl->v - l->cl->v;
        if(lval >= k) {
            r = r->cl;
            l = l->cl;
        } else {
            k -= lval;
            r = r->cr;
            l = l->cr;
        }
    }
    return r->r;
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<pii> in(n);
    for(int i = 0; i < n; ++i) {
        cin >> in[i].x;
        in[i].y = i;
    }
    auto inc = in;
    sort(inc.begin(), inc.end());
    map<int, int> newpos;
    for(int i = 0; i < n; ++i) {
        newpos[inc[i].x] = i + 1;
    }

    ver[0] = build(1, n);
    for(int i = 0; i < n; ++i) {
        int k = newpos[in[i].x];
        ver[i + 1] = ch(ver[i], k, 1);
    }

    int m;
    cin >> m;
    for(int t = 0; t < m; ++t) {
        int i, j, k;
        cin >> i >> j >> k;
        int a = que(i, j, k) - 1;
        cout << inc[a].y + 1 - i + 1 << "\n";
    }
}