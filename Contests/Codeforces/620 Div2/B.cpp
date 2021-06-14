#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

bool isPalin(string& s) {
	int l = 0, r = s.size() - 1;
	while (l < r) {
		if (s[l] != s[r]) { return false; }
		l++; r--;
	}
	return true;
}

int main() {
	int n, m; cin >> n >> m;

	int ans = 0; bool palindrome = false; string pal = "";
	set<string> here; string sss = "";
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (isPalin(s)) { palindrome = true; pal = s; }
		else {
			here.insert(s); 
			string need = s;
			reverse(need.begin(), need.end());
			if (here.count(need)) { sss += s; ans += 2 * m; }
		}
	}

	string toAdd = sss; reverse(toAdd.begin(), toAdd.end());
	if (palindrome) { ans += m; sss += pal; }
	
	cout << ans << endl;
	cout << sss << toAdd << endl;
}