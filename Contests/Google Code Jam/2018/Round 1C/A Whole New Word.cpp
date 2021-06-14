#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

struct node {
	char val;
	set<char> childVal;
	map<char, node*> child;

	node() {}
	node(char v) : val(v) {}
};

void addStr(node* root, string& s) {
	node* cur = root;

	for (int i = 0; i < s.size(); i++) {
		if (cur->childVal.count(s[i])) { cur = cur->child[s[i]]; }
		else {
			node* newN = new node(s[i]);
			cur->childVal.insert(s[i]);
			cur->child.insert({ s[i], newN });
			cur = newN;
		}
	}
}

string ans;
vector<set<int>> canUse;

bool dfs(int depth, node* v) {
	if (depth >= canUse.size()) { return false; }
	if (v->val != '#') ans.push_back(v->val);
	if (v->childVal.size() < canUse[depth].size()) {
		for (int a : canUse[depth]) {
			if (v->childVal.count(a) == 0) {
				ans.push_back(a); return true;
			}
		}
	}
	else {
		for (auto& v2 : v->child) {
			bool b = dfs(depth + 1, v2.second);
			if (b) { return true; }
		}
	}
	if (v->val != '#') ans.pop_back();
	return false;
}

//was enough to check first n+1 word in brute force way using canUse
int main() {
	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int N, L; cin >> N >> L;

		canUse.clear();	 canUse.resize(L);
		node* root = new node('#');
		for (int i = 0; i < N; i++) {
			string s; cin >> s;
			addStr(root, s);
			for (int j = 0; j < L; j++)
				canUse[j].insert(s[j]);
		}

		ans = "";

		cout << "Case #" << q << ": ";
		if (dfs(0, root)) {
			while (ans.size() < L) { ans.push_back(*canUse[ans.size()].begin()); }
			cout << ans << endl;
		}
		else {
			cout << "-" << endl;
		}
	}
}