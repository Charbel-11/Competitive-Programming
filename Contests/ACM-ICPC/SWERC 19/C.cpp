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

	int n; cin >> n;
	set<int> seen;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (s[0] == '-') { continue; }
		if (s.size() > 7) { continue; }
		seen.insert(stoi(s));
	}

	int ans = 0;
	while (seen.count(ans)) { ans++; }

	cout << ans << '\n';
}