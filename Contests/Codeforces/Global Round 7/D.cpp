#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> prefixFunction(string& s) {
	vector<int> pf(s.size(), 0);
	for (int i = 1; i < s.size(); i++) {
		int j = pf[i - 1];
		while (j > 0 && s[j] != s[i]) { j = pf[j - 1]; }
		if (s[j] == s[i]) { j++; }
		pf[i] = j;
	}
	return move(pf);
}

int main() {
	int t; cin >> t;

	while (t--) {
		string s; cin >> s;

		string start = "";
		int l = 0, r = s.size() - 1;
		while (l < r) {
			if (s[l] != s[r]) { break; }
			start.push_back(s[l]);
			l++; r--;
		}
		string end = start; reverse(end.begin(), end.end());
		if (l == r) { cout << start << s[l] << end << endl; continue; }

		int longestMidPal = 0; bool prefix = true;
		//Prefix
		string mid = s.substr(l, r - l + 1);
		string temp = mid + '#';
		reverse(mid.begin(), mid.end());
		temp += mid;
		auto pf = prefixFunction(temp);
		longestMidPal = pf.back();

		//Suffix
		temp = mid + '#';
		reverse(mid.begin(), mid.end());
		temp += mid;
		pf = prefixFunction(temp);
		if (pf.back() > longestMidPal) {
			longestMidPal = pf.back();
			prefix = false;
		}

		cout << start;
		if (prefix) { cout << s.substr(l, longestMidPal); }
		else { cout << s.substr(r - longestMidPal + 1, longestMidPal); }
		cout << end << endl;
	}
}