#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct node {
	int f;
	bool eow, root;
	vector<node*> neighbors;

	node() {}
	node(bool b, bool r) : eow(b), root(r) { f = 0; neighbors.resize(26, NULL); }
};

void addStr(node* root, string& s) {	
	for (int i = 0; i < s.size(); i++) {
		int idx = s[i] - 'A';

		if (root->neighbors[idx] == NULL) { root->neighbors[idx] = new node(0, 0); }
		if (i == s.size() - 1) { root->neighbors[idx]->eow = true; }
		else { root = root->neighbors[idx]; }
	}
}

void dfs(node* root) {
	if (!root) { return; }

	for (int i = 0; i < 26; i++) {
		if (root->neighbors[i]) {
			dfs(root->neighbors[i]);
			root->f += root->neighbors[i]->f;
		}
	}

	if (root->eow) { root->f++; }
	if (root->f >= 2 && !root->root) { root->f -= 2; }
}

int main() {
	int T; cin >> T;

	for (int z = 1; z <= T; z++) {
		int N; cin >> N;

		node* root = new node(0, 1);
		for (int i = 0; i < N; i++) {
			string s; cin >> s;
			reverse(s.begin(), s.end());
			addStr(root, s);
		}
		
		dfs(root);

		cout << "Case #" << z << ": " << N - root->f << endl;
	}
}