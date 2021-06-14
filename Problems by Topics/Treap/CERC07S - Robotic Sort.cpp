//https://www.spoj.com/problems/CERC07S/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

//Supports reversing a subarray along with dynamic insertion/deletion all in O(logn)
//Each function takes a node as input, this node will be the root of a treap
struct node {
	int priority, size;
	pair<int, int> val, minV;
	bool reverse;
	node *l, *r;

	node() {}
	node(int v, int id) :val({ v, id }), priority(rand()), l(NULL), r(NULL), size(1), reverse(0), minV({ v, id }) { }

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	void combine() {
		minV = val;
		if (l && l->minV < minV) { minV = l->minV; }
		if (r && r->minV < minV) { minV = r->minV; }
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

int find_min(node *t, int add = 0)
{
	lazy(t); int cur_pos = sz(t->l) + add + 1;
	if (t->r && t->r->minV == t->minV) return find_min(t->r, cur_pos);
	if (t->l && t->l->minV == t->minV) return find_min(t->l, add);
	return cur_pos;
}
//Inserts x at the end of the array represented by root
void insert(node *&root, node *x) {
	if (!root) { root = x; return; }
	merge(root, root, x);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N; cin >> N;
	while (N) {
		node *treap = NULL;
		for (int i = 0; i < N; i++) {
			int x; cin >> x;
			insert(treap, new node({ x,i }));
		}

		for (int i = 1; i <= N; i++) {
			int k = find_min(treap);
			node *l, *r;
			split(treap, l, r, k - 1);
			split(r, treap, r, 1);
			if (l) { l->reverse = 1; }
			merge(treap, l, r);

			cout << i + k - 1 << " ";
		}
		cout << endl;

		cin >> N;
	}
}