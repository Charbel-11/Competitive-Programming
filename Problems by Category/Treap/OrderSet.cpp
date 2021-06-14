//https://www.spoj.com/problems/ORDERSET/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
	int val, priority, size;
	node *l, *r;

	node() {}
	node(int v) :val(v), priority(rand()), l(NULL), r(NULL), size(1) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
};

struct treap {
	node *root;

	treap() { root = NULL; }

	int sz(node* t) { return t ? t->size : 0; }

	//Splits the subtree rooted at t into two trees according to curval (l <= and r >)
	//It will set l as the root of the l subtree and r as the root of the r subtree
	void split(node *t, node *&l, node *&r, int curVal) {
		if (!t) { l = r = NULL; }
		else if (t->val <= curVal) { split(t->r, t->r, r, curVal); l = t; }
		else { split(t->l, l, t->l, curVal); r = t; }
		if (t) t->updateSize();
	}

	//merges two treaps l and r and stores the root in u
	//assumes nodes in l have < vals than nodes in r
	void merge(node *&t, node *l, node *r) {
		if (!l || !r) { t = l ? l : r; }
		else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
		else { merge(r->l, l, r->l); t = r; }
		if (t) t->updateSize();
	}

	bool find(node *cur, int key) {
		if (!cur) { return false; }
		if (cur->val == key) { return true; }
		return find(cur->val < key ? cur->r : cur->l, key);
	}

	void insert(int key) { if (!find(root, key)) insert(root, new node(key)); }
	//Inserts u into the treap rooted at t
	void insert(node *&t, node *u) {
		if (!t) { t = u; }
		else if (u->priority > t->priority) { split(t, u->l, u->r, u->val); t = u; }
		else { insert(t->val <= u->val ? t->r : t->l, u); }
		if (t) t->updateSize();
	}

	void erase(int key) { erase(root, key); }
	//Erases the node with val k in the subtree of t
	void erase(node *& t, int key) {
		if (!t) { return; }
		if (t->val == key) { node* tmp = t; merge(t, t->l, t->r); delete tmp; }
		else { erase(t->val < key ? t->r : t->l, key); }
		if (t) t->updateSize();
	}

	int findKth(int k, node *cur) {
		if (sz(cur->l) >= k) { return findKth(k, cur->l); }
		if (sz(cur->l) == k - 1) { return cur->val; }
		return findKth(k - sz(cur->l) - 1, cur->r);
	}

	int count(int key, node *cur) {
		if (!cur) { return 0; }
		if (cur->val >= key) { return count(key, cur->l); }
		else { return sz(cur->l) + 1 + count(key, cur->r); }
	}
};

int main() {
	int Q; cin >> Q;
	treap S;
	while (Q--) {
		char q; cin >> q;
		int i; cin >> i;
		if (q == 'I') { S.insert(i); }
		else if (q == 'D') { S.erase(i); }
		else if (q == 'K') {
			if (i > S.sz(S.root)) { cout << "invalid" << endl; }
			else { cout << S.findKth(i, S.root) << endl; }
		}
		else { cout << S.count(i, S.root) << endl; }
	}
}