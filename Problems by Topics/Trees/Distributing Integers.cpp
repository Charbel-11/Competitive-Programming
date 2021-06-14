//https://atcoder.jp/contests/abc160/tasks/abc160_f

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = (ll)1e9 + 7;
const ll INF = 1e17;

// a*x - b*y = return value = GCD(a,b). x,y >= 0
ll egcd(ll a, ll b, ll &x, ll &y) { // MINUS B*Y
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}

	ll d = egcd(b, a%b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}
// modular inverse; works for any mod p (coprime with a)
ll inverse(ll a, ll p=mod) {
	ll x, y;
	egcd(a%p + p, p, x, y);
	return x % p;
}

ll fact[(int)2e5 + 1];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < 2e5 + 1; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
}

//Be sure to fillFact() before using this
//nCk with mod, uses mult inverse
//here assumes mod is prime, otherwise use egcd
ll choose(ll n, ll k) {
	if (k > n) { return 0; }
	ll num = fact[n], denom = fact[k];
	denom *= fact[n - k]; denom %= mod;

	ll multInv = inverse(denom);
	num *= multInv; num %= mod;
	return num;
}

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };
vector<ll> ans;
//Everything is 0-indexed
struct tree {
	vector<node> nodes;
	vector<int> parent, subtreeSize;
	vector<ll> ways;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); parent.resize(n, -1); subtreeSize.resize(n, 1); ways.resize(n, 1); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		ll res = 1;
		vector<ll> childSubtree;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			parent[e.v] = u;
			dfs(e.v, u);
			subtreeSize[u] += subtreeSize[e.v];
			res *= ways[e.v]; res %= mod;
			childSubtree.push_back(subtreeSize[e.v]);
		}
		if (childSubtree.empty()) { return; }

		//Alternative: multiply by fact[childSubtree[u]-1] and then divide by fact[childSubtree[e.v]] for each child of u
		//(res*=ways[e.v] should still be used above)
		ll prefix = childSubtree[0];
		for (int i = 1; i < childSubtree.size(); i++) {
			ll cur = childSubtree[i]; prefix += cur;
			res *= choose(prefix, cur); res %= mod;
		}

		ways[u] = res;
	}

	void reroot(int u, int p) {
		ans[u] = ways[u];

		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }

			ll prevWaysU = ways[u], prevWaysV = ways[e.v];

			ways[u] *= inverse(ways[e.v]); ways[u] %= mod;
			ways[u] *= inverse(choose(n-1, subtreeSize[e.v])); ways[u] %= mod;
	
			subtreeSize[u] -= subtreeSize[e.v];
			subtreeSize[e.v] += subtreeSize[u];

			ways[e.v] *= ways[u]; ways[e.v] %= mod;
			ways[e.v] *= choose(n-1, subtreeSize[u]); ways[e.v] %= mod;

			reroot(e.v, u);

			ways[u] = prevWaysU; ways[e.v] = prevWaysV;

			subtreeSize[e.v] -= subtreeSize[u];
			subtreeSize[u] += subtreeSize[e.v];
		}
	}
};

int main() {
	fillFact();
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n-1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	ans.resize(n);
	t.dfs(0, -1);
	t.reroot(0, -1);

	for (auto &x : ans) { cout << x << endl; }
}