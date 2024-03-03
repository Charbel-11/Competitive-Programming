//https://www.spoj.com/problems/CERC07S/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    int priority, size;
    pair<int, int> val, minV;
    bool reverse;
    node *l, *r;

    node() {}
    node(int v, int id) :val({ v, id }), priority(rand()), l(NULL), r(NULL), size(1), reverse(0), minV({ v, id }) { }

    void updateSize() {
        size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
    }
    void combine() {
        minV = val;
        if (l && l->minV < minV) { minV = l->minV; }
        if (r && r->minV < minV) { minV = r->minV; }
    }
};

int sz(node* t) { return t ? t->size : 0; }

//Apply + propagate;
void lazy(node *t) {
    if (!t || !t->reverse) { return; }
    if (t->reverse){
        t->reverse = false; swap(t->l, t->r);
        if (t->l) { t->l->reverse ^= 1; }
        if (t->r) { t->r->reverse ^= 1; }
    }
}

void operation(node *t) {
    if (!t) { return; }
    lazy(t); lazy(t->l); lazy(t->r);
    t->combine();
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the left subtree and r as the root of the right subtree
//pos 1-indexed
void split(node *t, node *&l, node *&r, int pos, int add = 0) {
    if (!t) { l = r = NULL; return; }
    lazy(t); int curPos = add + sz(t->l);
    if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
    else { split(t->l, l, t->l, pos, add); r = t; }
    if (t) { t->updateSize(); operation(t); }
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < vals than nodes in r
void merge(node *&t, node *l, node *r) {
    lazy(l); lazy(r);
    if (!l || !r) { t = l ? l : r; }
    else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
    else { merge(r->l, l, r->l); t = r; }
    if (t) { t->updateSize(); operation(t); }
}

//Inserts x at the end of the array represented by root
void insert(node *&root, node *x) {
    if (!root) { root = x; return; }
    merge(root, root, x);
}

//Removes A[i] (1-indexed) from the array represented by root
void erase(node *&root, int i) {
    node *lt, *rt, *lt2, *rt2;
    split(root, lt, rt, i - 1);
    split(rt, lt2, rt2, 1);
    merge(root, lt, rt2);
}

//Reverses subarray [l,r] (1-indexed) in the array represented by t
void reverse(node *&t, int l, int r) {
    node *t1, *t2, *t3;
    split(t, t1, t2, l - 1);
    split(t2, t2, t3, r - l + 1);
    t2->reverse ^= 1;
    merge(t, t1, t2); merge(t, t, t3);
}

int find_min(node *t, int add = 0){
    lazy(t); int cur_pos = sz(t->l) + add + 1;
    if (t->r && t->r->minV == t->minV) return find_min(t->r, cur_pos);
    if (t->l && t->l->minV == t->minV) return find_min(t->l, add);
    return cur_pos;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N; cin >> N;
    while (N) {
        node *treap = NULL;
        for (int i = 0; i < N; i++) {
            int x; cin >> x;
            insert(treap, new node({ x,i }));
        }

        for (int i = 1; i <= N; i++) {
            int k = find_min(treap);
            node *l, *r;
            split(treap, l, r, k - 1);
            split(r, treap, r, 1);
            if (l) { l->reverse = 1; }
            merge(treap, l, r);

            cout << i + k - 1 << " ";
        }
        cout << endl;

        cin >> N;
    }
}
