#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
const int K = 26;	//size of the alphabet

vector<int> ans;

struct node {
	bool eow = false; int checked = -1;
	node* child[K], * p;
	node* link = NULL;	//points to the longest available proper suffix of the current prefix e.g. abc -> bc
	node* go[K];	// go[idx] returns child[idx] if available or link->child[idx] if available or link->link->child[idx]...
	char ch;
	vector<int> wordsIdx;
	int occ = 1e7;

	node(node* p = NULL, char _ch = '$') : p(p), ch(_ch) {
		for (int i = 0; i < K; i++) { child[i] = go[i] = NULL; }
	}
};

//To initialize, say Trie t; without ()
struct Trie {
	node* root;
	map<int, vector<node*>> eows;

	Trie() { root = new node(); }

	void addStr(string const& s, int idx) {
		node* cur = root;
		for (int i = 0; i < s.size(); i++) {
			int idx = s[i] - 'a';
			if (cur->child[idx] == NULL) {
				cur->child[idx] = new node(cur, s[i]);
				eows[i + 1].push_back(cur->child[idx]);
			}
			cur = cur->child[idx];
		}
		cur->eow = true;
		cur->wordsIdx.push_back(idx);
	}

	node* getLink(node* v) {
		if (v->link == NULL) {
			if (v == root || v->p == root) { v->link = root; }
			else { v->link = go(getLink(v->p), v->ch); }
		}
		return v->link;
	}

	node* go(node* v, char ch) {
		int idx = ch - 'a';
		if (v->go[idx] == NULL) {
			if (v->child[idx]) { v->go[idx] = v->child[idx]; }
			else { v->go[idx] = v == root ? root : go(getLink(v), ch); }
		}
		return v->go[idx];
	}

	//Returns true if v represents a suffix of a word in the trie
	//Memoized
	bool check(node* v, int pos) {
		if (!v || v == root) { return 0; }
		if (v->checked != -1) { return v->checked; }
		if (v->eow) { v->occ = pos; return v->checked = 1; }

		return v->checked = check(getLink(v), pos);
	}

	void dfs() {
		for (auto it = eows.rbegin(); it != eows.rend(); it++) {
			for (node* cur : it->second) {
				for (int idx : cur->wordsIdx) { ans[idx] = cur->occ; }
				node* nxt = getLink(cur);
				nxt->occ = min(nxt->occ, cur->occ);
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	int k; cin >> k;
	Trie t; ans.resize(k, 0);
	vector<int> len(k);
	for (int i = 0; i < k; i++) {
		string cur; cin >> cur;
		len[i] = cur.size();
		t.addStr(cur, i);
	}

	node* cur = t.root;
	for (int i = 0; i < s.size(); i++) {
		cur = t.go(cur, s[i]);
		t.check(cur, i + 1);
	}

	t.dfs();
	for (int i = 0; i < k; i++) { cout << (ans[i] == 1e7 ? -1 : ans[i] - len[i] + 1) << '\n'; }
}