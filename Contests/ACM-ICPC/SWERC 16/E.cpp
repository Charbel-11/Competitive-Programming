#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;
const int mod = 1000003;
const int K = 26;	//size of the alphabet

struct node;

int idxCnt = 0;
unordered_map<int, node*> idxToNode;

char idxToChar(int i) {
	if (i <= 9) { return '0' + i; }
	i -= 10;
	if (i <= 25) { return 'a' + i; }
	i -= 26;
	return 'A' + i;
}

struct node {
	bool eow = false; int checked = -1, idx;
	node *child[K], *p;
	node *link = NULL;	//points to the longest available proper suffix of the current prefix e.g. abc -> bc
	node *go[K];	// go[idx] returns child[idx] if available or link->child[idx] if available or link->link->child[idx]...
	char ch;

	node(node *p = NULL, char _ch = '$') : p(p), ch(_ch) {
		for (int i = 0; i < K; i++) { child[i] = go[i] = NULL; }
		idx = idxCnt++; idxToNode[idx] = this;
	}
};

//To initialize, say Trie t; without ()
struct Trie {
	node* root;

	Trie() { root = new node(); }

	void addStr(string const& s) {
		node* cur = root;
		for (int i = 0; i < s.size(); i++) {
			int idx = s[i] - 'a';
			if (cur->child[idx] == NULL) { cur->child[idx] = new node(cur, s[i]); }
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
		int idx = ch - 'a';
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

unordered_map<int, char> m = { {0, 'o'}, {1, 'i'}, {3, 'e'}, {5, 's'}, {7, 't'} };
vector<string> allWords;
string curWord;

int dp[22][1002][2][2][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int A, B; cin >> A >> B;
	int N; cin >> N; Trie t;
	vector<string> words(N); 
	for (auto &s : words) { cin >> s; t.addStr(s); }

	for (int j = 0; j < idxCnt; j++) {
		if (t.check(idxToNode[j])) { continue; }
		dp[B][j][1][1][1] = 1; 
	}

	for (int i = B - 1; i >= 0; i--) {
		for (int j = 0; j < idxCnt; j++) {
			if (t.check(idxToNode[j])) { continue; }

			for (int b1 = 0; b1 < 2; b1++) {
				for (int b2 = 0; b2 < 2; b2++) {
					for (int b3 = 0; b3 < 2; b3++) {
						for (int k = 0; k < 62; k++) {
							char c = idxToChar(k);

							int nb1 = b1, nb2 = b2, nb3 = b3;
							if ('0' <= c && c <= '9') { nb1 = 1; }
							else if ('a' <= c && c <= 'z') { nb2 = 1; }
							else { nb3 = 1; }
							 
							if ('A' <= c && c <= 'Z') { c = c - 'A' + 'a'; }
							else if ('0' <= c && c <= '9' && m.count(c - '0')) { c = m[c - '0']; }
				
							int newTrieIdx = 0;
							if ('a' <= c && c <= 'z') { newTrieIdx = t.go(idxToNode[j], c)->idx; }

							dp[i][j][b1][b2][b3] += dp[i + 1][newTrieIdx][nb1][nb2][nb3];
							dp[i][j][b1][b2][b3] %= mod;
						}
					}
				}
			}
		}
	}

	int ans = 0;
	for (int i = 0; i <= B - A; i++) {
		ans += dp[i][0][0][0][0];
		ans %= mod;
	}
	cout << ans << '\n';
}