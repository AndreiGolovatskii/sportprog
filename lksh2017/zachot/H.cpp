#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>


using namespace std;
struct node
{
    long long left, right;
    long long val;
    node * child_left, *child_right;
};

const long long INF = 1e9;

long long nod(long long a, long long b) {
    if (b == 0)
        return a;
    nod(b, a % b);
}

node* build(long long left, long long right, vector<int> &values) {
    if (left > right) return 0;
    node* res = new node;
    res->left = left;
    res->val = 0;
    res->right = right;
    if (left == right){
        res->child_left = res->child_right = 0;
        res->val = values[left];
    } else {
        long long mid = (left + right) / 2;
        res->child_left = build(left, mid, values);
        res->child_right = build(mid+1, right, values);
        res->val = nod(res->child_left->val, res->child_right->val);
    }
    return res;
}

void update(node* root, long long pos, long long new_val) {
    if (pos > root->right || pos < root->left)
        return;
    if (pos == root->left && pos == root->right) {
        root->val += new_val;
        return;
    }
    update(root->child_left, pos, new_val);
    update(root->child_right, pos, new_val);
    root->val = nod(abs(root->child_left->val), abs(root->child_right->val));
}

long long query(node* root, long long left, long long right) {
    if (left > root->right || right < root->left)
        return 0;
    if (left <= root->left && right >= root->right)
        return abs(root->val);
    return nod(query(root->child_left, left, right), query(root->child_right, left, right));
}


int main(){
    vector<int> val(pow(2, 17) + 1, 0);
    node * root = build(1, pow(2, 17), val);
    int q;
    cin >> q;
    for (int o = 0; o < q; ++o) {
        long long ty;
        cin >> ty;
        if (ty == 0) {
            int l, r;
            cin >> l >> r;
            cout << query(root, l, r) << endl;
        } else {
            int i, x;
            cin >> i >> x;
            update(root, i, x);
        }
    }
    system("pause");
}

