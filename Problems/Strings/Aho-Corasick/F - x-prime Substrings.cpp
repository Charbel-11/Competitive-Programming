#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int K = 10;
const int INF = 1e7;

int X;
vector<string> bad;

struct node {
	bool eow = false; int checked = -1;
	node *child[K], *p;
	node *link = NULL;	//points to the longest available proper suffix of the current prefix e.g. abc -> bc
	node *go[K];	// go[idx] returns child[idx] if available or link->child[idx] if available or link->link->child[idx]...
	char ch;
	int idx;

	node(int _idx, node *p = NULL, char _ch = '$') : idx(_idx), p(p), ch(_ch) {
		for (int i = 0; i < K; i++) { child[i] = go[i] = NULL; }
	}
};

//To initialize, say Trie t; without ()
struct Trie {
	node* root;
	vector<node*> nodes;

	Trie() { root = new node(0); nodes.push_back(root); }

	void addStr(string const& s) {
		node* cur = root;
		for (int i = 0; i < s.size(); i++) {
			int idx = s[i] - '0';
			if (cur->child[idx] == NULL) { 
				cur->child[idx] = new node(nodes.size(), cur, s[i]);
				nodes.push_back(cur->child[idx]);
			}
			cur = cur->child[idx];
		}
		cur->eow = true;
	}

	node* getLink(node *v) {
		if (v->link == NULL) {
			if (v == root || v->p == root) { v->link = root; }
			else { v->link = go(getLink(v->p), v->ch); }
		}
		return v->link;
	}

	node* go(node *v, char ch) {
		int idx = ch - '0';
		if (v->go[idx] == NULL) {
			if (v->child[idx]) { v->go[idx] = v->child[idx]; }
			else { v->go[idx] = v == root ? root : go(getLink(v), ch); }
		}
		return v->go[idx];
	}

	//returns true if v represents a suffix of a word in the trie
	bool check(node *v) {
		if (!v || v == root) { return 0; }
		if (v->checked != -1) { return v->checked; }
		if (v->eow) { return v->checked = 1; }

		return v->checked = check(getLink(v));
	}
};

bool check(string const& str) {
	int n = (int)str.size();
	for (int i = 0; i < n; i++) {
		int cur = 0;
		for (int j = i; j < n; j++) {
			cur += str[j] - '0';
			if (cur != X && X % cur == 0) { return false; }
		}
	}
	return true;
}

void generate(string str, int sum) {
	if (sum > X) { return; }
	if (sum == X){
		if (check(str)) { bad.push_back(str); }
		return;
	}

	for (int i = 1; i <= 9; i++) {
		if (sum + i > X) { break; }
		generate(str + (char)('0' + i), sum + i);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	cin >> X;
	generate("", 0);
	Trie t;
	for (auto &s : bad) { t.addStr(s); }

	int N = t.nodes.size();
	vector<int> dp(N, INF); dp[0] = 0;

	for (char &c : s) {
		vector<int> newDP(N, INF);

		for (int i = 0; i < N; i++) {
			newDP[i] = min(newDP[i], dp[i] + 1);
			int nxt = t.go(t.nodes[i], c)->idx;

			if (!t.check(t.nodes[nxt])) { newDP[nxt] = min(newDP[nxt], dp[i]); }
		}

		swap(dp, newDP);
	}

	cout << *min_element(dp.begin(), dp.end()) << '\n';
}