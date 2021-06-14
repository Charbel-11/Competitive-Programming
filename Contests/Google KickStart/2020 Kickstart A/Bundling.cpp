#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
int N, K;

struct node {
	int pCount, contribution;
	vector<node*> child;

	node() { pCount = contribution = 0; child.resize(26, NULL); }
};

//To initialize, say Trie t; without ()
struct Trie {
	node* root;

	Trie() { root = new node(); }

	void addStr(string& s) {
		node* cur = root;
		for (int i = 0; i < s.size(); i++) {
			int idx = s[i] - 'A';

			if (cur->child[idx] == NULL) { cur->child[idx] = new node(); }
			cur = cur->child[idx];
			cur->pCount++;
		}
	}
};

//Works since a subtree only affects its ancestors, not another subtree at the same level
int dfs(node* cur) {
	int used = 0;
	for (int i = 0; i < 26; i++) {
		if (cur->child[i]) {
			int p = dfs(cur->child[i]);
			cur->pCount -= p; used += p;
			cur->contribution += cur->child[i]->contribution;
		}
	}

	cur->contribution += cur->pCount / K;
	used += (cur->pCount / K) * K;

	return used;
}

int sum(node* cur) {
	int res = cur->contribution;
	for (int i = 0; i < 26; i++) {
		if (cur->child[i]) {
			res += sum(cur->child[i]);
		}
	}
	return res;
}

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		cin >> N >> K;
		Trie t;
		for (int i = 0; i < N; i++) {
			string temp; cin >> temp;
			t.addStr(temp);
		}

		dfs(t.root);

		cout << "Case #" << z + 1 << ": " << sum(t.root) << endl;
	}
}