#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct node {
	int priority, size;
	ll val;
	node* l, * r;

	node() {}
	node(ll v) :val(v), priority(rand()), l(NULL), r(NULL), size(1) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree
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

void inOrder(node* cur, vector<int> &res) {
	if (!cur) { return; }
	inOrder(cur->l, res);
	res.push_back(cur->val);
	inOrder(cur->r, res);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	node* treap = NULL;
	for (int i = 1; i <= n; i++) { insert(treap, new node(i)); }

	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r;
		if (l >= r) { continue; }
		int range = min(r - l, n - r + 1);

		node* p1, * p2, * p3, * p4, * p5;
		split(treap, p1, p2, l - 1);
		split(p2, p2, p3, range);
		split(p3, p3, p4, r - l - range);
		split(p4, p4, p5, range);
		merge(treap, p1, p4);
		merge(treap, treap, p3);
		merge(treap, treap, p2);
		merge(treap, treap, p5);
	}

	vector<int> ans;
	inOrder(treap, ans);
	for (auto& x : ans) { cout << x << ' '; }
	cout << '\n';
}