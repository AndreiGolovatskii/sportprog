#include <bits/stdc++.h>

using namespace std;

struct node{
    int prior, cnt;
    string key;
    node* cl, * cr;
    node(){cl = cr = NULL;}
    node(string key) : key(key), prior(rand()), cnt(1), cl(NULL), cr(NULL){}
};
int cnt(node *root) {
    if(root) {
        return root->cnt;
    } else {
        return 0;
    }
}

void upd(node* &root) {
    if(root) {
        root -> cnt = cnt(root->cl) + cnt(root->cr) + 1;

    }
}


void split(node* &tl, node* & tr, node* t, string key) {
    if (!t)
        tr = tl = NULL;
    else if (t -> key < key) {
        split(t->cr, tr, t->cr, key);
        tl = t;
        upd(tr);
        upd(tl);
    } else {
        split(tl, t->cl, t->cl, key);
        tr = t;
        upd(tr);
        upd(tl);
    }
}

node* merge(node* t1, node* t2) {
    if(!t1)
        return t2;
    if(!t2)
        return t1;
    else if(t1->prior > t2->prior) {
        t1->cr = merge(t1->cr, t2);
        upd(t1);
        return t1;
    } else {
        t2->cl = merge(t1, t2->cl);
        upd(t2);
        return t2;
    }
}

void insert(node* &root, node* k){
    node* t1 = NULL, *t2 = NULL;
    split(t1, t2, root, k->key);
    t1 = merge(t1, k);
    root = merge(t1, t2);
}
string find(node *root, int k) {
    while(true) {
        if (cnt(root->cl) >= k) {
            root = root -> cl;
        } else if(cnt(root->cl) + 1 < k){
            k -= cnt(root->cl) + 1;
            root = root -> cr;
        } else {
            return root->key;
        }
    }
}

bool cmp(node * a, node* b){
    return a->key < b->key;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    node* root = NULL;
    for(int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if(s[0] >= 'a' && s[0] <= 'z') {
            insert(root, new node(s));
        } else {
            int k = stoi(s);
            cout << find(root, k) << "\n";
        }
    }
}