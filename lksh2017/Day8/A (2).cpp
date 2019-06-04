#include <vector>
#include <iostream>

using namespace std;

struct node
{
    int left, right, val;
    node * child_left, *child_right;
};

const int INF=1e9;

node* build(int left, int right, vector<int> &values) {
    if (left > right) return 0;
    node* res = new node;
    res->left = left;
    res->val = 0;
    res->right = right;
    if (left == right){
        res->child_left = res->child_right = 0;
        res->val = values[left];
    } else {
        int mid=(left + right) / 2;
        res->child_left = build(left, mid, values);
        res->child_right = build(mid+1, right, values);
        res->val = res->child_left->val + res->child_right->val;
    }
    return res;
}

void update(node* root, int pos, int new_val) {
    if(pos > root->right || pos < root->left)
        return;
    if (pos == root->left && pos == root->right) {
        root->val = new_val;
        return;
    }
    update(root->child_left, pos, new_val);
    update(root->child_right, pos, new_val);
    root->val = root->child_left->val + root->child_right->val;
}


int query(node* root, int left, int right) {
    if (left>root->right||right<root->left)
        return 0;
    if (left <= root->left && right >= root->right)
        return root->val;
    return query(root->child_left, left, right) + query(root->child_right, left, right);
}
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> vals(n + 1, 0);

    node *root = build(1, n, vals);
    int l, r;
    char com;
    for (int i = 0; i < k; ++i) {
        cin >> com >> l >> r;
        if (com == 'A') {
            update(root, l, r);
        } else {
            cout << query(root, l, r)<<endl;
        }
    }

}

