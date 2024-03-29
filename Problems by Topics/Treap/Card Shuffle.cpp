//https://www.codechef.com/problems/CARDSHUF

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

//Supports reversing a subarray along with dynamic insertion/deletion all in O(logn)

struct node {
	int priority, size, val;
	bool reverse;
	node *l, *r;

	node() {}
	node(int v) :val(v), priority(rand()), l(NULL), r(NULL), size(1), reverse(0) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

void lazy(node *t) {
	if (!t || !t->reverse) { return; }
	t->reverse = false;
	swap(t->l, t->r);
	if (t->l) { t->l->reverse ^= 1; }
	if (t->r) { t->r->reverse ^= 1; }
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree
void split(node *t, node *&l, node *&r, int pos, int add = 0) {
	if (!t) { l = r = NULL; return; }
	lazy(t); int curPos = add + sz(t->l);
	if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
	else { split(t->l, l, t->l, pos, add); r = t; }
	if (t) { t->updateSize(); }
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < vals than nodes in r
void merge(node *&t, node *l, node *r) {
	lazy(l); lazy(r);
	if (!l || !r) { t = l ? l : r; }
	else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	if (t) { t->updateSize(); }
}

//Inserts x at the end of the array represented by root
void insert(node *&root, node *x) {
	if (!root) { root = x; return; }
	merge(root, root, x);
}
//Inserts x at position i (1-indexed!) in the array represented by root
void insert(node *&root, node *x, int i) {
	node *lt, *rt;
	split(root, lt, rt, i - 1);
	merge(root, lt, x);
	merge(root, root, rt);
}
//Removes A[i] from the array represented by root
void erase(node *&root, int i) {
	node *lt, *rt, *lt2, *rt2;
	split(root, lt, rt, i - 1);
	split(rt, lt2, rt2, 1);
	merge(root, lt, rt2);
}

//Update ith element in subtree of root
void pointUpdate(node *&root, int i, ll newVal) {
	node *lt, *rt, *lt2, *rt2;
	split(root, lt, rt, i - 1); split(rt, lt2, rt2, 1);
	lt2->val = newVal;
	merge(root, lt, lt2); merge(root, root, rt2);
}

//Reverses subarray [l,r] in the subtree of t
void reverse(node *&t, int l, int r) {
	node *t1, *t2, *t3;
	split(t, t1, t2, l - 1);
	split(t2, t2, t3, r - l + 1);
	t2->reverse ^= 1;
	merge(t, t1, t2);
	merge(t, t, t3);
}

//Prints the array represented by cur in reverse order
void print(node *cur) {
	if (!cur) { return; }
	lazy(cur);
	print(cur->r);
	cout << cur->val << " ";
	print(cur->l);
}

int main() {
	int n, m; cin >> n >> m;
	node *d1 = NULL;
	for (int i = 0; i < n; i++) {
		insert(d1, new node(n - i));
	}

	node *d2, *d3, *d4;
	while (m--) {
		int A, B, C; cin >> A >> B >> C;

		//d1 has n-A, d2 has A
		split(d1, d1, d2, n - A);

		//d1 has n-A-B, d2 has A, d3 has B
		split(d1, d1, d3, n - A - B);

		//d1 has n-B, d3 has B
		merge(d1, d1, d2);

		//d1 has n-B-C, d3 has B, d4 has C
		split(d1, d1, d4, n - B - C);

		reverse(d3, 1, B);
		merge(d1, d1, d3);
		merge(d1, d1, d4);
	}
	print(d1); cout << endl;
}