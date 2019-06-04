#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;


struct node
{
    int left, right;
    long long min;
    node * child_left, *child_right;
};

vector<node *> lev;
const int INF=1e9;

node* build(int left, int right, vector<int> &values) {
    if (left > right) return 0;
    node* res = new node;
    res->left = left;
    res->min = 0;
    res->right = right;
    if (left == right){
        res->child_left = res->child_right = 0;
        res->min = values[left];
        lev.push_back(res);
    } else {
        int mid=(left + right) / 2;
        res->child_left = build(left, mid, values);
        res->child_right = build(mid+1, right, values);
        res->min = min(res->child_left->min, res->child_right->min);
    }
    return res;
}

void calc(node * root) {
    if (root->child_left->min > root->min) {
        root->child_right->min = root->min;
    }
    if (root->child_right->min > root->min) {
        root->child_left->min = root->min;
    }
    if (root->left != root->right)
        return;
    calc(root->child_left);
    calc(root->child_right);
}

void query(node* root, int left, int right, int ans) {
    if (left > root->right || right < root->left)
        return;
    if (left <= root->left && right >= root->right) {
        if (root->min > ans)
            return;
        root->min = ans;
        return;
    }
    query(root->child_left, left, right, ans);
    query(root->child_right, left, right, ans);
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> val (n + 1, -INF);
    node *root = build(1, n, val);
    for (int i = 0; i < m; ++i) {
        int l, r, q;
        cin >> l >> r >> q;
        query(root, l, r, q);
    }
    for (auto i : lev) {
        cout << i->min << " ";
    }
    calc(root);
    system("pause");
}

