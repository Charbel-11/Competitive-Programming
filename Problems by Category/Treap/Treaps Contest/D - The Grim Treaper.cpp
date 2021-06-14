#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e15;	//Change if needed
enum Type { MIN, ADD };

struct node {
	int priority, size;
	ll val = 0, sum = 0, max1 = -INF, max2 = -INF;
	ll lazyAdd = 0;
	int freqMax = 0;
	node* l, * r;

	node() {}
	node(ll v) : priority(rand()), l(NULL), r(NULL), size(1) {
		sum = max1 = val = v;
		freqMax = 1; max2 = -INF;
	}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	void combine() {
		sum = val + (l ? l->sum : 0) + (r ? r->sum : 0);
		assert(lazyAdd == 0);

		max1 = -INF; max2 = -INF; freqMax = 0; 
		vector<ll> values; values.push_back(val);
		if (l) { values.push_back(l->max1); values.push_back(l->max2); }
		if (r) { values.push_back(r->max1); values.push_back(r->max2); }
		sort(values.begin(), values.end());
		values.erase(unique(values.begin(), values.end()), values.end());

		max1 = values.back(); values.pop_back();
		if (!values.empty()) { max2 = values.back(); }
		if (max1 == val) { freqMax++; }
		if (l && max1 == l->max1) { freqMax += l->freqMax; }
		if (r && max1 == r->max1) { freqMax += r->freqMax; }
	}

	//Applies changes of type at node si using val
	void updateVal(const ll _val, const Type type) {
		if (type == MIN) {
			sum += (_val - max1) * freqMax; 
			if (val == max1) { val = _val; }
			max1 = _val;
		}
		else if (type == ADD) {
			if (max1 != INF) { max1 += _val; }
			if (max2 != -INF) { max2 += _val; }
			lazyAdd += _val; 
			sum += _val * size; val += _val;
		}
	}
};

int sz(node* t) { return t ? t->size : 0; }

void lazy(node* t) {
	if (!t) { return; }
	if (t->lazyAdd) {
		if (t->l) { t->l->updateVal(t->lazyAdd, ADD); }
		if (t->r) { t->r->updateVal(t->lazyAdd, ADD); }
		t->lazyAdd = 0;
	}
	if (t->l && t->max1 < t->l->max1) { 
		t->l->updateVal(t->max1, MIN);
	}
	if (t->r && t->max1 < t->r->max1) {
		t->r->updateVal(t->max1, MIN);
	}
}

void operation(node* t) {
	if (!t) { return; }
	t->combine();
}

//Splits the subtree rooted at t into two trees according pos (pos is in the left subtree)
//It will set l as the root of the left subtree and r as the root of the right subtree
//pos 1-indexed
void split(node* t, node*& l, node*& r, int pos, int add = 0) {
	if (!t) { l = r = NULL; return; }
	lazy(t); int curPos = add + sz(t->l);
	if (curPos < pos) { split(t->r, t->r, r, pos, curPos + 1); l = t; }
	else { split(t->l, l, t->l, pos, add); r = t; }
	if (t) { t->updateSize(); operation(t); }
}

void merge(node*& t, node* l, node* r) {
	lazy(l); lazy(r);
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

//Returns sum[l,r] (1-indexed) in the array represented by t
ll rangeQuery(node*& t, int l, int r) {
	node* L, * mid, * R;
	split(t, L, mid, l - 1);  split(mid, t, R, r - l + 1);
	ll ans = t->sum + t->lazyAdd;
	merge(mid, L, t); merge(t, mid, R);
	return ans;
}

void updateRangeMin(node* t, ll val) {
	if (!t) { return; }
	if (t->max1 <= val) { return; }
	if (t->max2 <= val) {
		t->updateVal(val, MIN);
	}
	else {
		lazy(t);
		updateRangeMin(t->l, val);
		updateRangeMin(t->r, val);
		if (t->val > val) { t->val = val; }
		t->updateSize(); operation(t);
	}
}

void rangeMin(node*& t, int l, int r, ll val) {
	node* L, * mid, * R;
	split(t, L, mid, l - 1); split(mid, t, R, r - l + 1);
	updateRangeMin(t, val);
	merge(mid, L, t); merge(t, mid, R);
}

void rangeAdd(node*& t, int l, int r, ll val) {
	node* L, * mid, * R;
	split(t, L, mid, l - 1); split(mid, t, R, r - l + 1);
	t->updateVal(val, ADD);
	merge(mid, L, t); merge(t, mid, R);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	node* treap = NULL;
	for (int i = 0; i < n; i++) {
		ll cur; cin >> cur;
		insert(treap, new node(cur));
	}

	while (q--) {
		int t, l, r; cin >> t >> l >> r;
		if (t == 1) {
			ll h; cin >> h;
			rangeMin(treap, l, r, h);
		}
		else if (t == 2) {
			node* lR, *rR;
			split(treap, lR, treap, l - 1);
			split(treap, treap, rR, r - l + 1);
			merge(rR, lR, rR);
			merge(treap, rR, treap);
		}
		else {
			ll x; cin >> x;
			rangeAdd(treap, l, r, x);
		}
		cout << rangeQuery(treap, 1, n) << '\n';
	}
}