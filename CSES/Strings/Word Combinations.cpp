#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const int K = 26;	//size of the alphabet
const ll mod = 1e9 + 7;

struct node {
	int f = 0;
	bool eow = false;
	node* child[K];

	node() { for (int i = 0; i < K; i++) { child[i] = NULL; } }
};

//To initialize, say Trie t; without ()
struct Trie {
	node* root;

	Trie() { root = new node(); }

	void addStr(string const& s) {
		node* cur = root;
		for (int i = 0; i < (int)s.size(); i++) {
			int idx = s[i] - 'a';
			if (cur->child[idx] == NULL) { cur->child[idx] = new node(); }
			cur = cur->child[idx];
		}
		cur->eow = true;
	}

	bool findWord(string const& word) {
		node* cur = root;
		for (int i = 0; i < (int)word.size(); i++) {
			int idx = word[i] - 'a';
			if (cur->child[idx] == NULL) { return false; }
			cur = cur->child[idx];
		}
		return cur->eow;	//return true if we want a prefix
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string t; cin >> t;
	int n = t.size();
	Trie trie;
	int k; cin >> k;
	for (int i = 0; i < k; i++) {
		string s; cin >> s;
		trie.addStr(s);
	}

	vector<ll> dp(n + 1, 0); dp[n] = 1;
	for (int i = n - 1; i >= 0; i--) {
		node* cur = trie.root;
		for (int j = i; j < n; j++) {
			int idx = t[j] - 'a';
			if (!cur->child[idx]) { break; }
			cur = cur->child[idx];
			if (cur->eow) { dp[i] += dp[j + 1]; dp[i] %= mod; }
		}
	}

	cout << dp[0] << '\n';
}