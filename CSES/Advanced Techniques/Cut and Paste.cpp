#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

//Building the treap in O(n) doesn't make it that much faster than using the insert 
//at the end of the array n times
struct node {
	int priority, size;
	char val;
	node* l, * r;

	node() {}
	node(ll v) :val(v), priority(rand()), l(NULL), r(NULL), size(1) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree; l/r can be = t
//pos 1-indexed
void split(node* t, node*& l, node*& r, int pos, int add = 0) {
	if (!t) { l = r = NULL; return; }
	int curPos = add + sz(t->l);
	if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
	else { split(t->l, l, t->l, pos, add); r = t; }
	if (t) { t->updateSize(); }
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < keys than nodes in r
//l/r can be = t
void merge(node*& t, node* l, node* r) {
	if (!l || !r) { t = l ? l : r; }
	else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	if (t) { t->updateSize(); }
}

//Inserts x at the end of the array represented by root
void insert(node*& root, node* x) {
	if (!root) { root = x; return; }
	merge(root, root, x);
}

void print(node* cur) {
	if (!cur) { return; }
	print(cur->l);
	cout << cur->val;
	print(cur->r);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	string s; cin >> s;
	node* treap = NULL;
	for (auto& c : s) { insert(treap, new node(c)); }

	while (m--) {
		int l, r; cin >> l >> r;
		node* lR, *rR;
		split(treap, lR, treap, l - 1);
		split(treap, treap, rR, r - l + 1);
		merge(rR, lR, rR);
		merge(treap, rR, treap);
	}

	print(treap);
}