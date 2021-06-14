//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1620
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int K = 52;	//size of the alphabet

vector<bool> found;

int getIdx(char c) {
	int idx = c - 'a';
	if (c >= 'A' && c <= 'Z') { idx = c - 'A' + 26; }
	return idx;
}

struct node {
	bool eow = false, checked = false;
	vector<int> sIdx;
	node *child[K], *p;
	node *link = NULL;	//points to the longest available proper suffix of the current prefix e.g. abc -> bc or c, aba -> ba or a
	node *go[K];	// go[idx] returns child[idx] if available or link->child[idx] if available or link->link->child[idx]...
	char ch;

	node(node *p = NULL, char _ch = '$') : p(p), ch(_ch) {
		for (int i = 0; i < K; i++) { child[i] = go[i] = NULL; }
	}
};

//To initialize, say Trie t; without ()
struct Trie {
	node* root;

	Trie() { root = new node(); }

	void addStr(string const& s, int sIdx) {
		node* cur = root;
		for (int i = 0; i < (int)s.size(); i++) {
			int idx = getIdx(s[i]);
			if (cur->child[idx] == NULL) { cur->child[idx] = new node(cur, s[i]); }
			cur = cur->child[idx];
		}
		cur->eow = true;
		cur->sIdx.push_back(sIdx);
	}
	
	//Overall in linear time due to memoization
	node* getLink(node *v) {
		if (v->link == NULL) {
			if (v == root || v->p == root) { v->link = root; }
			else { v->link = go(getLink(v->p), v->ch); }
		}
		return v->link;
	}

	node* go(node *v, char ch) {
		int idx = getIdx(ch);
		if (v->go[idx] == NULL) {
			if (v->child[idx]) { v->go[idx] = v->child[idx]; }
			else { v->go[idx] = v == root ? root : go(getLink(v), ch); }
		}
		return v->go[idx];
	}

	void check(node *v) {
		if (!v || v == root) { return; }
		if (v->checked) { return; }
		v->checked = true;

		if (v->eow) { 
			for(auto &i : v->sIdx)
				found[i] = 1; 
		}
		check(getLink(v));
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T; cin >> T;
	while (T--) {
		string s; cin >> s;
		int q; cin >> q;
		found.clear(); found.resize(q, 0);

		Trie trie;
		for(int i = 0; i < q; i++){
			string t; cin >> t;
			trie.addStr(t, i);
		}

		node *cur = trie.root;
		for (auto &c : s) {
			cur = trie.go(cur, c);
			trie.check(cur);
		}

		for (auto b : found) {
			cout << (b ? 'y' : 'n') << '\n';
		}
	}
}