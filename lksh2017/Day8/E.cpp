#include <vector>
#include <iostream>

using namespace std;

struct node {
    int left, right, min;
    node * child_left, *child_right;
};

const int INF=1e9;

node* build(int left, int right, vector<int> &values) {
    if (left > right) return 0;
    node* res = new node;
    res->left = left;
    res->min = INF;
    res->right = right;
    if (left == right){
        res->child_left = res->child_right = 0;
        res->min = values[left];
    } else {
        int mid=(left + right) / 2;
        res->child_left = build(left, mid, values);
        res->child_right = build(mid+1, right, values);
        res->min = min(res->child_left->min, res->child_right->min);
    }
    return res;
}

void update(node* root, int pos, int new_val) {
    if (pos > root->right || pos < root->left)
        return;
    if (pos == root->right && pos == root->left) {
        root->min = new_val;
        return;
    }
    update(root->child_left, pos, new_val);
    update(root->child_right, pos, new_val);
    root->min = min(root->child_left->min, root->child_right->min);
}

int query(node* root, int left, int right) {
    if (left>root->right||right<root->left)
        return INF;
    if (left <= root->left && right >= root->right)
        return root->min;
    return min(query(root->child_left, left, right), query(root->child_right, left, right));
}


int main()
{
    vector<int> val(2e5);
    for (int i = 0; i < 2e5 + 1; ++i) {
        val[i] = i;
    }

    node * root = build(1, 2e5, val);

    int n, a;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        if (a < 0) {
            a = -a;
            update(root, a, a);
        } else {
            int pos = query(root, a, 2e5);
            update(root, pos, 1e9);
            cout <<pos <<endl;
        }
    }
}
