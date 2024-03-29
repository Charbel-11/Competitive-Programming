//http://www.spoj.com/problems/HORRIBLE/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    int priority, size;
    ll val, sum, lazy; bool reverse;
    node *l, *r; node() {}
    node(ll v) :val(v), priority(rand()), l(NULL), r(NULL), size(1), sum(val), lazy(0), reverse(0) {}

    void updateSize() { size = 1 + (l ? l->size : 0) + (r ? r->size : 0); }
    void combine() { sum = val + (l ? l->sum : 0) + (r ? r->sum : 0); }
};

int sz(node* t) { return t ? t->size : 0; }

//Apply + propagate;
void lazy(node *t) {
    if (!t || (!t->lazy && !t->reverse)) { return; }
    // lazy and reverse have to be associative or need to change op to propagate l, r, cur, l, r
    if (t->lazy) {
        t->val += t->lazy;            //lazy operation; CHANGE IT
        t->sum += t->lazy * sz(t);    //Adds the contribution of lazy for the whole segment
        if (t->l) { t->l->lazy += t->lazy; }    //propagate lazy
        if (t->r) { t->r->lazy += t->lazy; }
        t->lazy = 0;
    }
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
//Inserts x at position i (1-indexed) in the array represented by root
void insert(node *&root, node *x, int i) {
    if (!root) { root = x; return; }
    node *lt, *rt;
    split(root, lt, rt, i - 1);
    merge(root, lt, x);
    merge(root, root, rt);
}
//Removes A[i] (1-indexed) from the array represented by root
void erase(node *&root, int i) {
    node *lt, *rt, *lt2, *rt2;
    split(root, lt, rt, i - 1);
    split(rt, lt2, rt2, 1);
    merge(root, lt, rt2);
}

//Updates A[i] (1-indexed) in the array represented by root
void pointUpdate(node *&root, int i, ll newVal) {
    node *lt, *rt, *lt2, *rt2;
    split(root, lt, rt, i - 1); split(rt, lt2, rt2, 1);
    lt2->val = newVal;
    merge(root, lt, lt2); merge(root, root, rt2);
}

//Adds val to [l,r] (1-indexed) in the array represented by t (lazy update)
void rangeUpdate(node *&t, int l, int r, ll val) {
    node *L, *mid, *R;
    split(t, L, mid, l - 1); split(mid, t, R, r - l + 1);
    t->lazy += val;	//Lazy update
    merge(mid, L, t); merge(t, mid, R);
}

//Reverses subarray [l,r] (1-indexed) in the array represented by t
void reverse(node *&t, int l, int r) {
    node *t1, *t2, *t3;
    split(t, t1, t2, l - 1);
    split(t2, t2, t3, r - l + 1);
    t2->reverse ^= 1;
    merge(t, t1, t2); merge(t, t, t3);
}

//Returns sum[l,r] (1-indexed) in the array represented by t
ll rangeQuery(node *&t, int l, int r) {
    node *L, *mid, *R;
    split(t, L, mid, l - 1);  split(mid, t, R, r - l + 1);
    ll ans = t->sum;
    merge(mid, L, t); merge(t, mid, R);
    return ans;
}

int main() {
	int t; cin >> t;
	while (t--) {
		int n, c; cin >> n >> c;
		node *treap = NULL;
		for (int i = 0; i < n; i++) { insert(treap, new node(0)); }
		while (c--) {
			int cc; cin >> cc;
			if (cc == 0) {
				int p, q, v; cin >> p >> q >> v;
				rangeUpdate(treap, p, q, v);
			}
			else {
				int l, r; cin >> l >> r;
				cout << rangeQuery(treap, l, r) << endl;
			}
		}
	}
}