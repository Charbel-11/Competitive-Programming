#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct node {
	int val, priority, size;
	node* l, * r;

	node() {}
	node(int v) :val(v), priority(rand()), l(NULL), r(NULL), size(1) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

//Splits the subtree rooted at t into two trees according to curval (l <= and r >)
//It will set l as the root of the l subtree and r as the root of the r subtree
void split(node* t, node*& l, node*& r, int curVal) {
	if (!t) { l = r = NULL; }
	else if (t->val <= curVal) { split(t->r, t->r, r, curVal); l = t; }
	else { split(t->l, l, t->l, curVal); r = t; }
	if (t) t->updateSize();
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < vals than nodes in r
void merge(node*& t, node* l, node* r) {
	if (!l || !r) { t = l ? l : r; }
	else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	if (t) t->updateSize();
}

//Inserts u into the treap rooted at t
void insert(node*& t, node* u) {
	if (!t) { t = u; }
	else if (u->priority > t->priority) { split(t, u->l, u->r, u->val); t = u; }
	else { insert(t->val <= u->val ? t->r : t->l, u); }
	if (t) t->updateSize();
}

//Erases the node with val k in the subtree of t
void erase(node*& t, int key) {
	if (!t) { return; }
	if (t->val == key) { node* tmp = t; merge(t, t->l, t->r); delete tmp; }
	else { erase(t->val < key ? t->r : t->l, key); }
	if (t) t->updateSize();
}

//Assumes k is <= number of nodes
int findKth(node* cur, int k) {
	if (sz(cur->l) >= k) { return findKth(cur->l, k); }
	if (sz(cur->l) == k - 1) { return cur->val; }
	return findKth(cur->r, k - sz(cur->l) - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int k; cin >> k;
		int n; cin >> n;
		vector<int> needed(n); for (auto& x : needed) { cin >> x; }
		vector<int> ans(k + 1);

		node* treap = NULL;
		for (int i = 1; i <= k; i++) { insert(treap, new node(i)); }

		int cur = 0;
		for (int i = 1; i <= k; i++) {
			cur += i; cur %= treap->size;
			if (cur == 0) { cur = treap->size; }
			int idx = findKth(treap, cur);
			erase(treap, idx);
			ans[idx] = i;
			cur--;
		}

		cout << "Case #" << qq << ": ";
		for (auto& x : needed) { cout << ans[x] << ' '; } cout << '\n';
	}
}