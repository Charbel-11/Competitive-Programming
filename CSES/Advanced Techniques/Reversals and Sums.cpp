#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

//Supports reversing a subarray along with dynamic insertion/deletion all in O(logn)
//Each function takes a node as input, this node will be the root of a treap
struct node {
	int priority, size;
	ll val = 0, s = 0;
	bool reverse;
	node* l, * r;

	node() {}
	node(int v) :val(v), s(v), priority(rand()), l(NULL), r(NULL), size(1), reverse(0) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	void combine() {
		s = val + (l ? l->s : 0) + (r ? r->s : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

void lazy(node* t) {
	if (!t || !t->reverse) { return; }
	t->reverse = false;
	swap(t->l, t->r);
	if (t->l) { t->l->reverse ^= 1; }
	if (t->r) { t->r->reverse ^= 1; }
}

void operation(node* t) {
	if (!t) { return; }
	lazy(t->l); lazy(t->r);
	t->combine();
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree
//pos 1-indexed
void split(node* t, node*& l, node*& r, int pos, int add = 0) {
	if (!t) { l = r = NULL; return; }
	lazy(t); int curPos = add + sz(t->l);
	if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
	else { split(t->l, l, t->l, pos, add); r = t; }
	if (t) { t->updateSize(); operation(t); }
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < vals than nodes in r
void merge(node*& t, node* l, node* r) {
	lazy(l); lazy(r);
	if (!l || !r) { t = l ? l : r; }
	else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	if (t) { t->updateSize(); operation(t); }
}

//Inserts x at the end of the array represented by root
void insert(node*& root, node* x) {
	if (!root) { root = x; return; }
	merge(root, root, x);
}

//Reverses subarray [l,r] (1-indexed) in the array represented by t
void reverse(node*& t, int l, int r) {
	node* t1, * t2, * t3;
	split(t, t1, t2, l - 1);
	split(t2, t2, t3, r - l + 1);
	t2->reverse ^= 1;
	merge(t, t1, t2);
	merge(t, t, t3);
}

ll findSum(node*& t, int l, int r) {
	if (l > r) { return 0; }
	node* t1, * t2, * t3;
	split(t, t1, t2, l - 1);
	split(t2, t2, t3, r - l + 1);
	operation(t2);
	ll res = t2 ? t2->s : 0;
	merge(t, t1, t2);
	merge(t, t, t3);
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	node* treap = NULL;
	for (int i = 0; i < n; i++) { ll x; cin >> x; insert(treap, new node(x)); }

	while (m--) {
		int t; cin >> t;
		int l, r; cin >> l >> r; 
		if (t == 1) { reverse(treap, l, r); }
		else { cout << findSum(treap, l, r) << '\n'; }
	}
}