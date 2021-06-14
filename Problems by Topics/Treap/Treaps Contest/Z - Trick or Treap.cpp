#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;

struct node {
	int priority, size;
	ll val, sum;
	node* l, * r, * p;

	node() {}
	node(ll v) :val(v), priority(rand()), l(NULL), r(NULL), size(1), sum(val), p(NULL) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	//Combining left subarray, cur element, right subarray
	void combine() {
		p = NULL;
		if (l) { l->p = this; }
		if (r) { r->p = this; }
		sum = val + (l ? l->sum : 0) + (r ? r->sum : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

void operation(node* t) {
	if (!t) { return; }
	t->combine();
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the l subtree and r as the root of the r subtree; l/r can be = t
//pos 1-indexed
void split(node* t, node*& l, node*& r, int pos, int add = 0) {
	if (!t) { l = r = NULL; return; }
	int curPos = add + sz(t->l);
	if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
	else { split(t->l, l, t->l, pos, add); r = t; }
	if (t) { t->updateSize(); operation(t); }
}

//merges two treaps l and r and stores the root in t
//assumes nodes in l have < keys than nodes in r
//l/r can be = t
void merge(node*& t, node* l, node* r) {
	if (!l || !r) { t = l ? l : r; }
	else if (l->priority > r->priority) { merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	if (t) { t->updateSize(); operation(t); }
}

//Inserts x at the end of the array represented by root
void insert(node*& root, node* x) {
	if (!root) { root = x; return; }
	merge(root, root, x);
}
//Inserts x at position i (1-indexed) in the array represented by root
void insert(node*& root, node* x, int i) {
	if (!root) { root = x; return; }
	node* lt, * rt;
	split(root, lt, rt, i - 1);
	merge(root, lt, x);
	merge(root, root, rt);
}
//Removes A[i] (1-indexed) from the array represented by root
void erase(node*& root, int i) {
	node* lt, * rt, * lt2, * rt2;
	split(root, lt, rt, i - 1);
	split(rt, lt2, rt2, 1);
	merge(root, lt, rt2);
}

//Updates A[i] (1-indexed) in the array represented by root
void pointUpdate(node*& root, int i, ll newVal) {
	node* lt, * rt, * lt2, * rt2;
	split(root, lt, rt, i - 1); split(rt, lt2, rt2, 1);
	lt2->val = newVal;
	merge(root, lt, lt2); merge(root, root, rt2);
}

//Returns sum[l,r] (1-indexed) in the array represented by t
ll rangeQuery(node*& t, int l, int r) {
	node* L, * mid, * R;
	split(t, L, mid, l - 1);  split(mid, t, R, r - l + 1);
	ll ans = t->sum;
	merge(mid, L, t); merge(t, mid, R);
	return ans;
}

node* getRoot(node* u) {
	while (u->p) { u = u->p; }
	return u;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	map<int, node*> m;
	int q; cin >> q;
	for (int i = 1; i <= q; i++) {
		int t; cin >> t;
		if (t == 1) {
			ll y; cin >> y;
			node* cur = new node(y);
			m[i] = cur;
		}
		else if (t == 2) {
			int y, z; cin >> y >> z;
			node* rY = getRoot(m[y]);
			node* rZ = getRoot(m[z]);
			if (rY != rZ) {
				merge(rY, rY, rZ);
			}
		}
		else if (t == 3) {
			int y, z; cin >> y >> z;
			node* rY = getRoot(m[y]);
			if (rY->size > z) {
				split(rY, rY, rY, z);
			}
		}
		else {
			int y; cin >> y;
			node* rY = getRoot(m[y]);
			cout << rY->sum << '\n';
		}
	}
}