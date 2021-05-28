//http://poj.org/problem?id=3580
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

struct node {
	int priority, size;
	int val, lazy, minV;
	bool reverse;
	node *l, *r;

	node() {}
	node(int v) :val(v), priority(rand()), l(NULL), r(NULL), size(1), reverse(0), lazy(0), minV(val) { }

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	void combine() {
		minV = val;
		if (l) { minV = min(minV, l->minV); }
		if (r) { minV = min(minV, r->minV); }
	}
};

int sz(node* t) { return t ? t->size : 0; }

void lazy(node *t) {
	if (!t) { return; }
	if (t->reverse) {
		t->reverse = false;
		swap(t->l, t->r);
		if (t->l) { t->l->reverse ^= 1; }
		if (t->r) { t->r->reverse ^= 1; }
	}

	if (t->lazy) {
		t->val += t->lazy;
		t->minV += t->lazy;
		if (t->l) { t->l->lazy += t->lazy; }
		if (t->r) { t->r->lazy += t->lazy; }
		t->lazy = 0;
	}
}

void operation(node *t) {
	if (!t) { return; }
	lazy(t->l); lazy(t->r);
	t->combine();
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree
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

//Reverses subarray [l,r] (1-indexed) in the array represented by t
void reverse(node *&t, int l, int r) {
	node *t1, *t2, *t3;
	split(t, t1, t2, l - 1);
	split(t2, t2, t3, r - l + 1);
	t2->reverse ^= 1;
	merge(t, t1, t2);
	merge(t, t, t3);
}

//Returns min[l,r] (1-indexed) in the array represented by t
int rangeQuery(node *&t, int l, int r) {
	node *L, *mid, *R;
	split(t, L, mid, l - 1);  split(mid, t, R, r - l + 1);
	int ans = t->minV;
	merge(mid, L, t); merge(t, mid, R);
	return ans;
}

//Adds val to [l,r] (1-indexed) in the array represented by t
void rangeUpdate(node *&t, int l, int r, int val) {
	node *L, *mid, *R;
	split(t, L, mid, l - 1); split(mid, t, R, r - l + 1);
	t->lazy += val;	//Lazy update
	merge(mid, L, t); merge(t, mid, R);
}

void revolve(node *&treap, int l, int r, int t) {
	t %= (r - l + 1);
	t += (r - l + 1); t %= (r - l + 1);
	if (t == 0) { return; }

	node *l1, *r1, *l2, *r2;
	split(treap, l1, r1, l - 1);
	split(r1, l2, r2, r - l + 1);

	node *cutL, *cutR;
	split(l2, cutL, cutR, r - l + 1 - t);
	merge(l2, cutR, cutL);
	merge(r1, l2, r2);
	merge(treap, l1, r1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	node *treap = NULL;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		insert(treap, new node(x));
	}

	int M; cin >> M;
	while (M--) {
		string op; cin >> op;
		if (op == "ADD") {
			int x, y; cin >> x >> y;
			int d; cin >> d;
			rangeUpdate(treap, x, y, d);
		}
		else if (op == "REVERSE") {
			int x, y; cin >> x >> y;
			reverse(treap, x, y);
		}
		else if (op == "REVOLVE") {
			int x, y; cin >> x >> y;
			int t; cin >> t;
			revolve(treap, x, y, t);
		}
		else if (op == "INSERT") {
			int x; int P;
			cin >> x; cin >> P;
			insert(treap, new node(P), x+1);
		}
		else if (op == "DELETE") {
			int x; cin >> x;
			erase(treap, x);
		}
		else if(op=="MIN") {
			int x, y; cin >> x >> y;
			cout << rangeQuery(treap, x, y) << '\n';
		}
	}
}