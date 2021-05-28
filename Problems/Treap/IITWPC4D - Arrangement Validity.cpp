//https://www.spoj.com/problems/IITWPC4D/

#include <iostream>
#include <numeric>
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

void heapify(node *t) {
	if (!t) { return; }
	node *max = t;
	if (t->l != NULL && t->l->priority > max->priority)
		max = t->l;
	if (t->r != NULL && t->r->priority > max->priority)
		max = t->r;
	if (max != t) {
		swap(t->priority, max->priority);
		heapify(max);
	}
}
//Builds a treap in O(n) given a SORTED array, with random priorities
node* build(vector<int> &a, int i, int j) {
	if (i > j) return NULL;
	int mid = (i + j) / 2;
	node *t = new node(a[mid]);
	t->l = build(a, i, mid - 1);
	t->r = build(a, mid + 1, j);
	heapify(t);
	if (t) t->updateSize();
	return t;
}

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

int main() {
	int T; cin >> T;
	for (int qq = 1; qq <= T; qq++) {
		int n; cin >> n;
		vector<int> nums(n), H(n), ans(n, -1);
		for (int i = 0; i < n; i++) { nums[i] = i + 1; cin >> H[i]; }
		node *treap = build(nums, 0, n - 1);

		bool OK = true;
		for (int i = n - 1; i >= 0; i--) {
			int needed = i - H[i] + 1;
			if (needed <= 0 || needed > treap->size) { OK = false; break; }
			ans[i] = findKth(treap, needed);
			erase(treap, ans[i]);
		}

		cout << "Test : " << qq << endl;
		if (!OK) { cout << -1 << endl; }
		else { for (auto &x : ans) { cout << x << " "; }cout << endl; }
	}
}