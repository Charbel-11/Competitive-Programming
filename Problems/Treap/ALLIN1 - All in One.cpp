//https://www.spoj.com/problems/ALLIN1/
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

//Use as a check in case of duplicates (if we want to allow duplicates, add a freq counter to node to avoid linear blow up)
//Make sure to put it at the start of another insert function that calls the current one (to avoid using find at each recursive call)
bool find(node *cur, int key) {
	if (!cur) { return false; }
	if (cur->val == key) { return true; }
	return find(cur->val < key ? cur->r : cur->l, key);
}

//Inserts u into the treap rooted at t
void insert(node *&t, node *u) {
	if (!t) { t = u; }
	else if (u->priority > t->priority) { split(t, u->l, u->r, u->val); t = u; }
	else { insert(t->val <= u->val ? t->r : t->l, u); }
	if (t) t->updateSize();
}

//Erases the node with val k in the subtree of t
void erase(node *&t, int key) {
	if (!t) { return; }
	if (t->val == key) { node* tmp = t; merge(t, t->l, t->r); delete tmp; }
	else { erase(t->val < key ? t->r : t->l, key); }
	if (t) t->updateSize();
}

int findKth(node *cur, int k) {
	if (sz(cur->l) >= k) { return findKth(cur->l, k); }
	if (sz(cur->l) == k - 1) { return cur->val; }
	return findKth(cur->r, k - sz(cur->l) - 1);
}

//Find number of elements < key
int count(node *cur, int key) {
	if (!cur) { return 0; }
	if (cur->val >= key) { return count(cur->l, key); }
	else { return sz(cur->l) + 1 + count(cur->r, key); }
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int q; cin >> q;
	node *treap = NULL;
	while (q != -1) {
		if (q == 1) {
			int n; cin >> n;
			insert(treap, new node(n));
		}
		else if (q == 2) {
			int n; cin >> n;
			erase(treap, n);
		}
		else if (q == 3) {
			int n; cin >> n;
			if (!find(treap, n)) { cout << -1 << '\n'; }
			else { cout << count(treap, n) + 1 << '\n'; }
		}
		else {
			int i; cin >> i;
			if (i == 0 || treap == NULL || i > treap->size) { cout << -1 << '\n'; }
			else { cout << findKth(treap, i) << '\n'; }
		}
		cin >> q;
	}
}