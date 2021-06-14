//https://www.spoj.com/problems/COUNT1IT/
//Treap implementation of multiset

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
	int val, priority, size;	//size accounts for duplicates here
	int freq;
	node *l, *r;

	node() {}
	node(int v) :val(v), priority(rand()), l(NULL), r(NULL), size(1), freq(1) {}

	void updateSize() {
		size = freq + (l ? l->size : 0) + (r ? r->size : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

//Splits the subtree rooted at t into two trees according to curval (l <= and r >)
//It will set l as the root of the l subtree and r as the root of the r subtree
void split(node *t, node *&l, node *&r, int curVal) {
	if (!t) { l = r = NULL; }
	else if (t->val <= curVal) { split(t->r, t->r, r, curVal); l = t; }
	else { split(t->l, l, t->l, curVal); r = t; }
	if (t) t->updateSize();
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < vals than nodes in r
void merge(node *&t, node *l, node *r) {
	if (!l || !r) { t = l ? l : r; }
	else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	if (t) t->updateSize();
}

//Use as a check in case of duplicates
bool find(node *cur, int key, bool add = 0) {
	if (!cur) { return false; }
	if (cur->val == key) { cur->freq += add; cur->updateSize(); return true; }
	bool b = find(cur->val < key ? cur->r : cur->l, key, add);
	if (b && add) cur->updateSize();
	return b;
}
 
//Inserts u into the treap rooted at t
void insertR(node *&t, node *u) {
	if (!t) { t = u; }
	else if (u->priority > t->priority) { split(t, u->l, u->r, u->val); t = u; }
	else { insertR(t->val <= u->val ? t->r : t->l, u); }
	if (t) t->updateSize();
}
//Deals with duplicates
void insert(node *&t, node *u) { if (!find(t, u->val, 1)) { insertR(t, u); } }

//Accounts for duplicates
int findKth(node *cur, int k) {
	if (sz(cur->l) >= k) { return findKth(cur->l, k); }
	if (sz(cur->l) <= k - 1 && sz(cur->l) >= k - cur->freq) { return cur->val; }
	return findKth(cur->r, k - sz(cur->l) - cur->freq);
}

//Find number of elements <= key
int count(node *cur, int key) {
	if (!cur) { return 0; }
	if (cur->val > key) { return count(cur->l, key); }
	else { return sz(cur->l) + cur->freq + count(cur->r, key); }
}

int main() {
	int n, q; cin >> n >> q;
	node *treap = NULL;
	for (int i = 0; i < n; i++) {
		int tmp; cin >> tmp;
		insert(treap, new node(tmp));
	}

	while (q--) {
		int id; cin >> id;
		if (id == 1) {
			int x; cin >> x;
			int a = count(treap, x);
			insert(treap, new node(x + a));
		}
		else if (id == 2) {
			int y; cin >> y;
			cout << count(treap, y) << endl;
		}
		else {
			int z; cin >> z;
			if (!treap || z > treap->size) { cout << "invalid" << endl; continue; }
			cout << findKth(treap, z) << endl;
		}
	}
}