#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	string ans = "";

	int seen = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'A') { seen |= 1; }
		else if (s[i] == 'C') { seen |= 2; }
		else if (s[i] == 'G') { seen |= 4; }
		else { seen |= 8; }

		if (seen == 15) { ans.push_back(s[i]); seen = 0; }
	}

	if ((seen | 1) > seen) { ans.push_back('A'); }
	else if ((seen | 2) > seen) { ans.push_back('C'); }
	else if ((seen | 4) > seen) { ans.push_back('G'); }
	else if ((seen | 8) > seen) { ans.push_back('T'); }

	cout << ans << '\n';
}