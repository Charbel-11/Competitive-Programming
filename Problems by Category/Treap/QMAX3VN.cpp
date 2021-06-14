//https://www.spoj.com/problems/QMAX3VN/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct node {
	int priority, size;
	int val, maxVal;
	node *l, *r;

	node() {}
	node(ll v) :val(v), priority(rand()), l(NULL), r(NULL), size(1), maxVal(val) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	//Combining left subarray, cur element, right subarray
	void combine() {
		maxVal = max({ val, (l ? l->maxVal : (int)-1e9-10), (r ? r->maxVal : (int)-1e9 - 10) });
	}
};

int sz(node* t) { return t ? t->size : 0; }

void operation(node *t) {
	if (!t) { return; }
	t->combine();
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree
void split(node *t, node *&l, node *&r, int pos, int add = 0) {
	if (!t) { l = r = NULL; return; }
	int curPos = add + sz(t->l);
	if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
	else { split(t->l, l, t->l, pos, add); r = t; }
	if (t) { t->updateSize(); operation(t); }
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < vals than nodes in r
void merge(node *&t, node *l, node *r) {
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

//Returns sum[l,r] (1-indexed) in the array represented by t
ll rangeQuery(node *t, int l, int r) {
	node *L, *mid, *R;
	split(t, L, mid, l - 1);  split(mid, t, R, r - l + 1);
	ll ans = t->maxVal;
	merge(mid, L, t); merge(t, mid, R);
	return ans;
}

int main() {
	int Q; cin >> Q;
	node *treap = NULL;
	while (Q--) {
		char q; cin >> q;
		if (q == 'A') {
			int height, pos; cin >> height >> pos;
			insert(treap, new node(height), pos);
		}
		else {
			int l, r; cin >> l >> r;
			cout << rangeQuery(treap, l, r) << endl;
		}
	}
}