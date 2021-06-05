#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> prefixFunction(string& s) {
	vector<int> pf(s.size(), 0);
	for (int i = 1; i < (int)s.size(); i++) {
		int j = pf[i - 1];
		while (j > 0 && s[j] != s[i]) { j = pf[j - 1]; }
		if (s[j] == s[i]) { j++; }
		pf[i] = j;
	}
	return move(pf);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	vector<int> pref = prefixFunction(s);
	vector<int> ans;
	int i = s.size() - 1; 
	while (i > 0 && pref[i] > 0) {
		ans.push_back(pref[i]);
		i = pref[i] - 1;
	}

	reverse(ans.begin(), ans.end());
	for (auto &x : ans) { cout << x << ' '; }
}