#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int K = 26;	//size of the alphabet

vector<int> ans;

struct node {
	bool eow = false; bool checked = 0;
	int idx = -1;
	node* child[K], * p;
	char ch;

	node(node* p = NULL, char _ch = '$') : p(p), ch(_ch) {
		for (int i = 0; i < K; i++) { child[i] = NULL; }
	}
};

struct Trie {
	node* root;

	Trie() { root = new node(); }

	void addStr(string const& s, int id) {
		node* cur = root;
		for (int i = 0; i < s.size(); i++) {
			int idx = s[i] - 'a';
			if (cur->child[idx] == NULL) { cur->child[idx] = new node(cur, s[i]); }
			cur = cur->child[idx];
		}
		cur->eow = true;
		cur->idx = id;
	}

	void reset(node* u) {
		if (!u) { return; }
		if (u->checked && u->eow) { ans.push_back(u->idx); }
		u->checked = 0;
		for (int i = 0; i < 26; i++) {
			if (u->child[i]) { reset(u->child[i]); }
		}
	}
};

void traverse(int i, int k, string& s, node* u, Trie& t) {
	//	cout << s << " " << i << " " << k << " " << u->ch << '\n';
	if (i >= s.size()) { u->checked = 1; }
	if (i < s.size()) {
		node* nxt = u->child[s[i] - 'a'];
		if (nxt) { traverse(i + 1, k, s, nxt, t); }
	}
	if (k) {
		for (int j = 0; j < 26; j++) {
			if (i < s.size() && j == s[i] - 'a') { continue; }
			node* nxt = u->child[j];
			if (nxt) {
				traverse(i, k - 1, s, nxt, t);
				traverse(i + 1, k - 1, s, nxt, t);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	freopen("corrector.in", "r", stdin);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		Trie t; vector<string> A(n);
		int id = 0;
		for (auto& x : A) { cin >> x; t.addStr(x, id++); }

		int Q; cin >> Q;
		while (Q--) {
			string s; cin >> s;
			traverse(0, 1, s, t.root, t);

			t.reset(t.root);
			if (ans.empty()) { cout << -1 << '\n'; }
			else {
				sort(ans.begin(), ans.end());
				for (auto& x : ans) { cout << x << ' '; }
				cout << '\n';
			}
			ans.clear();
		}
	}
}