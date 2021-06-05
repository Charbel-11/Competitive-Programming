//Array based implementation of a trie + Aho Corasick
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int K = 26;	//size of the alphabet

struct node {
	bool eow = false; int checked = -1;
	int child[K], p;
	int link = -1;	//points to the longest available proper suffix of the current prefix e.g. abc -> bc
	int go[K];	// go[idx] returns child[idx] if available or link->child[idx] if available or link->link->child[idx]...
	char ch;

	node(int _p = -1, char _ch = '$') : p(_p), ch(_ch) {
		for (int i = 0; i < K; i++) { child[i] = go[i] = -1; }
	}
};

//To initialize, say Trie t; without ()
struct Trie {
	int root;
	vector<node*> nodes;

	Trie() { nodes.push_back(new node()); root = 0; }

	void addStr(string const& s) {
		int cur = root;
		for (int i = 0; i < s.size(); i++) {
			int idx = s[i] - 'A';
			if (nodes[cur]->child[idx] == -1) {
				nodes[cur]->child[idx] = nodes.size();
				nodes.push_back(new node(cur, s[i]));
			}
			cur = nodes[cur]->child[idx];
		}
		nodes[cur]->eow = true;
	}

	int getLink(int v) {
		node* vn = nodes[v];
		if (vn->link == -1) {
			if (v == root || vn->p == root) { vn->link = root; }
			else { vn->link = go(getLink(vn->p), vn->ch); }
		}
		return vn->link;
	}

	int go(int v, char ch) {
		int idx = ch - 'A';
		node* vn = nodes[v];
		if (vn->go[idx] == -1) {
			if (vn->child[idx] != -1) { vn->go[idx] = vn->child[idx]; }
			else { vn->go[idx] = v == root ? root : go(getLink(v), ch); }
		}
		return vn->go[idx];
	}
};

ll dp[1003][102][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	string s; cin >> s;
	int m = s.size();

	Trie t;
	t.addStr(s);

	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= 1; k++) {
				for (int a = 0; a < 26; a++) {
					int nxt = t.go(j, a + 'A');
					dp[i + 1][nxt][k || (nxt == m)] += dp[i][j][k];
					dp[i + 1][nxt][k || (nxt == m)] %= mod;
				}
			}
		}
	}

	ll ans = 0;
	for (int i = 0; i <= m; i++) {
		ans += dp[n][i][1]; ans %= mod;
	}
	cout << ans << '\n';
}