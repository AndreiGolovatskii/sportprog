#include <bits/stdc++.h>

using namespace std;
#define pii pair<int, int>
#define x first
#define y second
const int MN = (int)1e5;
vector<int> g[MN];
int hStart[MN];
int heavy[MN];
int s[MN];
int p[MN], d[MN];
int bp[MN][35];

vector<vector<int>> paths;

int inPath[MN], posPath[MN];

void dfs(int u, int pi, int di) {
    p[u] = pi;
    d[u] = di;

    int su = 1;
    heavy[u] = -1;
    for(int v : g[u]) {
        if(v != pi) {
            dfs(v, u, di + 1);
            su += s[v];
        }
    }
    s[u] = su;

    for(int v : g[u]) {
        if(v != pi) {
            if(2 * s[v] >= s[u]) {
                heavy[u] = v;
            }
        }
    }
}
void refs(int s) {
    int k = paths.size();
    if(heavy[s] != -1) {
        return;
    }
    vector<int> path;
    while(true) {
        posPath[s] = path.size();
        path.push_back(s);
        inPath[s] = k;

        if(heavy[p[s]] == s) {
            s = p[s];
        } else {
            break;
        }
    }
    paths.push_back(path);
}
int lca(int u, int v) {
    if(d[v] > d[u]) {
        swap(u, v);
    }
    for(int i = 34; i >= 0; --i) {
        if(d[bp[u][i]] - d[v] >= 0) {
            u = bp[u][i];
        }
    }
    if(u == v) return v;
    for(int i = 34; i >= 0; --i) {
        if(bp[u][i] != bp[v][i]) {
            v = bp[v][i];
            u = bp[u][i];
        }
    }
    return p[v];
}

///-----------------///

struct node
{
    int left, right, max;
    node * cl, * cr;
};
vector<node *> treeRoots;
const int INF = (int)1e9;
node* build(int left, int right, vector<int> & values) {
    if (left > right)
        return 0;
    node * res = new node;
    res->left = left;
    res->right = right;
    if (right == left)
    {
        res->cl = res->cr = 0;
        res->max = hStart[values[left]];
    }
    else
    {
        int mid = (left + right) / 2;
        res->cl = build(left, mid, values);
        res->cr = build(mid + 1, right, values);
        res->max = max(res->cl->max, res->cr->max);
    }
    return res;
}
int query_max(node * root, int left, int right)  {
    if (right < root->left || left > root->right)
        return -INF;
    if (left <= root->left && right >= root->right)
        return root->max;
    int ans1 = query_max(root->cl, left, right);
    int ans2 = query_max(root->cr, left, right);
    return max(ans1, ans2);
}
void update(node * root, int idx, int val) {
    if (idx < root->left || idx > root->right)
        return;
    if (root->left == root->right)
    {
        root->max = val;
        return;
    }
    update(root->cl, idx, val);
    update(root->cr, idx, val);
    root->max = max(root->cl->max, root->cr->max);
}
///---------------///
int res(int u, int lc) {
    int mx = -1e9;
    while(inPath[u] != inPath[lc]) {
        node *root = treeRoots[inPath[u]];
        int r = query_max(root, posPath[u], paths[inPath[u]].size() - 1);
        mx = max(mx, r);
        u = paths[inPath[u]].back();
        u = p[u];
    }
    node *root = treeRoots[inPath[u]];
    int r = query_max(root, posPath[u], posPath[lc]);
    mx = max(mx, r);
    return mx;
}

void upd(int u, int nv) {
    int pathNum = inPath[u];
    int pos = posPath[u];
    node *root = treeRoots[pathNum];
    update(root, pos, nv);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> hStart[i];
    }
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(0, 0, 0);

    for(int i = 0; i < n; ++i) {
        refs(i);
    }

    for (int i = 0; i < n; ++i) {
        bp[i][0] = p[i];
    }
    for (int j = 1; j < 35; ++j) {
        for (int i = 0; i < n; ++i) {
            bp[i][j] = bp[bp[i][j - 1]][j - 1];
        }
    }

    for(auto i : paths) {
        treeRoots.push_back(build(0, i.size() - 1, i));
    }

    int k;
    cin >> k;
    for(int i = 0; i < k; ++i) {
        char t;
        cin >> t;
        if(t == '?') {
            int u, v;
            cin >> u >> v;
            u--; v--;
            int lc = lca(u, v);
            cout << max(res(u, lc), res(v, lc)) << "\n";
        } else {
            int u, nv;
            cin >> u >> nv;
            u--;
            upd(u, nv);
        }
    }
}