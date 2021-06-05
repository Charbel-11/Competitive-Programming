#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	vector<bool> seen(26, 0);
	string res;

	for (int i = 0; i < (int)s.size(); i++) {
		int cur = s[i] - 'A';
		if (seen[cur]) { res.push_back(s[i]); seen[cur] = 0; }
		else { seen[cur] = 1; }
	}
	bool odd = 0; int c = -1;
	for (int i = 0; i < 26; i++) {
		if (seen[i] && odd) { cout << "NO SOLUTION\n"; return 0; }
		if (seen[i]) { odd = 1; c = i; }
	}

	cout << res; 
	if (odd) { cout << (char)('A' + c); }
	reverse(res.begin(), res.end());
	cout << res << '\n';
}