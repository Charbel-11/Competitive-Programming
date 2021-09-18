#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int K = 2;	//size of the alphabet

struct node {
	node* child[K];
	node() { for (int i = 0; i < K; i++) { child[i] = NULL; } }
};

//To initialize, say Trie t; without ()
struct Trie {
	node* root;

	Trie() { root = new node(); }

	void addNum(const int x) {
		node* cur = root;
		for (int i = 30; i >= 0; i--) {
			bool b = ((1 << i) & x);
			if (cur->child[b] == NULL) { cur->child[b] = new node(); }
			cur = cur->child[b];
		}
	}

	int findMaxXor(const int x) {
		node* cur = root;

		int ans = 0;
		for (int i = 30; i >= 0; i--) {
			bool b = (1 << i) & x;
			if (cur->child[!b]) {
				cur = cur->child[!b];
				ans |= (1 << i);
			}
			else { cur = cur->child[b]; }
		}

		return ans;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> x(n); for (auto& xx : x) { cin >> xx; }
	for (int i = 1; i < n; i++) { x[i] ^= x[i - 1]; }

	int ans = 0;
	Trie t; t.addNum(0);
	for (int i = 0; i < n; i++) {
		ans = max(ans, t.findMaxXor(x[i]));
		t.addNum(x[i]);
	}

	cout << ans << '\n';
}