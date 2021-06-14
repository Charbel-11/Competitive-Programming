#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct DynamicHash {
	static const ll m1 = 8675309, m2 = 1e9 + 7;
	static const ll s1 = 257, s2 = 619;
	static const int SZ = 1e6;
	static ll s1Pow[SZ], s2Pow[SZ];
	static bool precomp;
	ll v1 = 0, v2 = 0; int l = 0;

	DynamicHash() {}
	DynamicHash(DynamicHash& oh) : v1(oh.v1), v2(oh.v2), l(oh.l) {}
	DynamicHash(string& s) {
		v1 = v2 = 0; l = 0;
		for (auto& c : s) { add(c); }
	}

	static void precompute() {
		if (precomp) { return; }
		precomp = true;
		s1Pow[0] = s2Pow[0] = 1;
		for (int i = 1; i < SZ; i++)
			s1Pow[i] = (s1Pow[i - 1] * s1) % m1;
		for (int i = 1; i < SZ; i++)
			s2Pow[i] = (s2Pow[i - 1] * s2) % m2;
	}

	void add(char c) {
		v1 = (v1 * s1 + c) % m1;
		v2 = (v2 * s2 + c) % m2;
		l++;
	}

	bool equal(DynamicHash& oh) {
		if (v1 != oh.v1) { return false; }
		return v2 == oh.v2;
	}

	void append(DynamicHash& oh) {
		precompute();
		v1 = (v1 * s1Pow[oh.l] + oh.v1) % m1;
		v2 = (v2 * s2Pow[oh.l] + oh.v2) % m2;
		l += oh.l;
	}
};

bool DynamicHash::precomp = false;
ll DynamicHash::s1Pow[SZ];
ll DynamicHash::s2Pow[SZ];

//Building the treap in O(n) doesn't make it that much faster than using the insert 
//at the end of the array n times
struct node {
	int priority, size;
	char c;
	DynamicHash hash1, hash2;
	node* l, * r;

	node() {}
	node(char _c) : priority(rand()), l(NULL), r(NULL), size(1), c(_c) { hash1.add(_c); hash2.add(_c); }

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
	}
	//Combining left subarray, cur element, right subarray
	void combine() {
		if (l) { hash1 = DynamicHash(l->hash1); }
		else { hash1 = DynamicHash(); }
		hash1.add(c);
		if (r) { hash1.append(r->hash1); }

		if (r) { hash2 = DynamicHash(r->hash2); }
		else { hash2 = DynamicHash(); }
		hash2.add(c);
		if (l) { hash2.append(l->hash2); }
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

void inOrder(node* cur, vector<char>& res) {
	if (!cur) { return; }
	inOrder(cur->l, res);
	res.push_back(cur->c);
	inOrder(cur->r, res);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	string s; cin >> s;
	node* treap = NULL;
	for (auto& c : s) { insert(treap, new node(c)); }

	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int l, r; cin >> l >> r;
			node* p1, *p2, *p3;
			split(treap, p1, p2, l - 1);
			split(p2, p2, p3, r - l + 1);
			merge(treap, p1, p3);
		}
		else if (t == 2) {
			char c; int p; cin >> c >> p;
			insert(treap, new node(c), p);
		}
		else {
			int l, r; cin >> l >> r;
			node* p1, * p2, * p3;
			split(treap, p1, p2, l - 1);
			split(p2, p2, p3, r - l + 1);

			bool isPal = (p2->hash1.equal(p2->hash2));
			cout << (isPal ? "yes" : "no") << '\n';

			merge(treap, p1, p2);
			merge(treap, treap, p3);
		}
	}
}