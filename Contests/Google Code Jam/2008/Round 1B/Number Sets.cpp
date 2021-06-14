#include <iostream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct DSU {
	vector<int> rank, parent;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

vector<bool> prime;
void generatePrimes(int n) {
	if (n < 1) { return; }
	prime.resize(n, true);
	prime[0] = prime[1] = false;

	for (ll i = 2; i < n; i++) {
		if (prime[i] == false) { continue; }
		for (ll j = i * i; j < n; j += i)
			prime[j] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	generatePrimes(1e6 + 5);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		ll A, B, P; cin >> A >> B >> P;
		cout << "Case #" << qq << ": ";
		if (P > B - A) { cout << B - A + 1 << '\n'; continue; }

		DSU dsu(B - A + 1);

		vector<ll> p;
		for (int i = P; i <= B - A; i++) { 
			if (prime[i]) { p.push_back(i); } 
		}

		//O(nlogn)
		for (auto& curP : p) {
			ll start = curP * ((A + curP - 1) / curP);
			ll i = start + curP;
			while (i <= B) {
				dsu.merge(start - A, i - A);
				i += curP;
			}
		}

		set<int> rem;
		for (int i = 0; i < B - A + 1; i++) {
			rem.insert(dsu.find(i));
		}
		cout << rem.size() << '\n';
	}
}