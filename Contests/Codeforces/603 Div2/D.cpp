#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <map>
#include <set>
using namespace std;

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

int main() {
	int n; cin >> n;

	vector<bool> here(26, 0);
	vector<string> pass;

	for (int i = 0; i < n; i++) {
		string temp; cin >> temp;
		pass.push_back(temp);
		for (auto &x : temp) { here[x - 'a'] = 1; }
	}

	DSU dsu(26);
	/*
	map<char, int> m;
	for (int i = 0; i < 26; i++) {
		if (here[i]) { m[i+'a'] = i; }
	}
	*/
	for (auto &word : pass) {
		int prevC = word[0];
		for (int i = 1; i < word.size(); i++) {
			int curC = word[i];
			dsu.merge(prevC-'a', curC-'a');
		}
	}

	set<int> taken;
	int res = 0;
	for (int i = 0; i < 26; i++) {
		if (here[i] && taken.count(dsu.find(i)) == 0) {
			res++; taken.insert(dsu.find(i));
		}
	}

	cout << res << endl;
}