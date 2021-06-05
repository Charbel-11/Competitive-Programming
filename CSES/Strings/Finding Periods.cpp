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

	string s; cin >> s; int n = s.size();
	vector<int> pref = prefixFunction(s);
	
	vector<int> prefVals;
	int k = n - 1;
	while (k > 0) { 
		prefVals.push_back(pref[k]);
		k = pref[k] - 1;
	}
	prefVals.push_back(0);
	reverse(prefVals.begin(), prefVals.end());

	vector<int> ans;
	for (int i = 0; i < n; i++) {
		if (binary_search(prefVals.begin(), prefVals.end(), n - i - 1)) { ans.push_back(i + 1); }
		//If i>n/2, then there is a partial match of first i characters
		//Otherwise, prefVal > i so there is an overlap and thus a period
	}

	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}