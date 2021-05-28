//https://www.spoj.com/problems/GSS6/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct node {
	int priority, size;
	ll val, prefSum, sufSum, maxSum, totalSum;
	node *l, *r;

	node() {}
	node(ll v) :val(v), priority(rand()), l(NULL), r(NULL), size(1), prefSum(val), sufSum(val), maxSum(val), totalSum(val) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	//Combining left subarray, cur element, right subarray
	void combine() {
		totalSum = val + (l ? l->totalSum : 0) + (r ? r->totalSum : 0);
		prefSum = max((l ? l->prefSum : (ll)-1e15), (l ? l->totalSum : 0) + val + max(0ll, (r ? r->prefSum : 0)));
		sufSum = max((r ? r->sufSum : (ll)-1e15), (r ? r->totalSum : 0) + val + max(0ll, (l ? l->sufSum : 0)));
		maxSum = max((l ? l->maxSum : (ll)-1e15), (r ? r->maxSum : (ll)-1e15));
		maxSum = max(maxSum, val + max((l ? l->sufSum : 0), 0ll) + max((r ? r->prefSum : 0), 0ll));
	}
};

int sz(node* t) { return t ? t->size : 0; }

void operation(node *t) {
	if (!t) { return; }
	t->combine();
}

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
//Builds a treap in O(n) given a sorted array, with random priorities
node* build(vector<int> &a, int i, int j) {
	if (i > j) return NULL;
	int mid = (i + j) / 2;
	node *t = new node(a[mid]);
	t->l = build(a, i, mid - 1);
	t->r = build(a, mid + 1, j);
	heapify(t);
	if (t) { t->updateSize(); operation(t); }
	return t;
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree
void split(node *t, node *&l, node *&r, int pos, int add = 0) {
	if (!t) { l = r = NULL; return; }
	int curPos = add + sz(t->l);
	if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
	else { split(t->l, l, t->l, pos, add); r = t; }
	if (t) { t->updateSize(); operation(t); }
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < vals than nodes in r
void merge(node *&t, node *l, node *r) {
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

//Updates A[i] (1-indexed) in the array represented by root
void pointUpdate(node *&root, int i, ll newVal) {
	node *lt, *rt, *lt2, *rt2;
	split(root, lt, rt, i - 1); split(rt, lt2, rt2, 1);
	lt2->val = newVal;
	merge(root, lt, lt2); merge(root, root, rt2);
}

//Returns sum[l,r] (1-indexed) in the array represented by t
ll rangeQuery(node *t, int l, int r) {
	node *L, *mid, *R;
	split(t, L, mid, l - 1);  split(mid, t, R, r - l + 1);
	ll ans = t->maxSum;
	merge(mid, L, t); merge(t, mid, R);
	return ans;
}

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }
	node *treap = build(nums, 0, n - 1);

	int Q; cin >> Q;
	while (Q--) {
		char qq; cin >> qq;
		if (qq == 'I') {
			int pos, y; cin >> pos >> y;
			insert(treap, new node(y), pos);
		}
		else if (qq == 'D') {
			int x; cin >> x;
			erase(treap, x);
		}
		else if (qq == 'R') {
			int pos, y; cin >> pos >> y;
			pointUpdate(treap, pos, y);
		}
		else if (qq == 'Q') {
			int x, y; cin >> x >> y;
			cout << rangeQuery(treap, x, y) << endl;
		}
	}
}