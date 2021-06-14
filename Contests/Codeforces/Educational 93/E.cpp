#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;

struct node {
	ll val; int priority, size;
	int light = 0, subLight = 0;
	ll subSum = 0;
	node *l, *r;

	node() {}
	node(ll v, int ll) :val(v), priority(rand()), l(NULL), r(NULL), size(1), subSum(val), light(ll), subLight(ll) {}

	void updateSize() {
		size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
		subSum = val + (l ? l->subSum : 0) + (r ? r->subSum : 0);
		subLight = light + (l ? l->subLight : 0) + (r ? r->subLight : 0);
	}
};

int sz(node* t) { return t ? t->size : 0; }

//Splits the subtree rooted at t into two trees according to curval (l <= and r >)
//It will set l as the root of the l subtree and r as the root of the r subtree
void split(node *t, node *&l, node *&r, ll curVal) {
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

//Inserts u into the treap rooted at t
void insert(node *&t, node *u) {
	if (!t) { t = u; }
	else if (u->priority > t->priority) { split(t, u->l, u->r, u->val); t = u; }
	else { insert(t->val <= u->val ? t->r : t->l, u); }
	if (t) t->updateSize();
}

//Erases the node with val k in the subtree of t
void erase(node *&t, ll key) {
	if (!t) { return; }
	if (t->val == key) { node* tmp = t; merge(t, t->l, t->r); delete tmp; }
	else { erase(t->val < key ? t->r : t->l, key); }
	if (t) t->updateSize();
}

pair<ll, int> sumAtKth(node *cur, int k) {
	if (sz(cur->l) >= k) {
		pair<ll, int> prevAns = sumAtKth(cur->l, k);
		prevAns.first += cur->val + (cur->r ? cur->r->subSum : 0);
		prevAns.second += cur->light + (cur->r ? cur->r->subLight : 0);
		return prevAns;
	}
	if (sz(cur->l) == k - 1) { 
		return { cur->val + (cur->r?cur->r->subSum:0), cur->light + (cur->r?cur->r->subLight:0) };
	}
	return sumAtKth(cur->r, k - sz(cur->l) - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	node *treap = NULL;
	ll totSum = 0, ans = 0;
	int numL = 0, numS = 0;

	set<ll> light;
	for (int i = 0; i < n; i++) {
		int type; cin >> type;
		ll d; cin >> d; 
		totSum += d; 
		if (d < 0) {
			erase(treap, -d);
			if (light.count(-d)) { numL--; light.erase(-d); }
			numS--;
		}
		else { 
			insert(treap, new node(d, type));
			if (type) { numL++; light.insert(d); }
			numS++;
		}

		if (numL == 0) { cout << totSum << '\n'; continue; }

		int idx = numS - numL + 1;
		pair<ll, int> curRes = sumAtKth(treap, idx);
		if (curRes.second == numL) {
			if (numL == numS) { ans = totSum + curRes.first - (*light.begin()); }
			else {
				curRes = sumAtKth(treap, idx - 1);
				ans = totSum + curRes.first - (*light.begin());
			}
		}
		else {
			ans = totSum + curRes.first;
		}

		cout << ans << '\n';
	}
}