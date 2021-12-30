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
	vector<pair<char, int>> v;
	for (int i = 0; i < s.size(); i++) { v.push_back({ s[i], i }); }
	sort(v.begin(), v.end());

	string ans = "";
	int idx = v[0].second;
	while (v[idx].first != '#') {
		ans.push_back(v[idx].first);
		idx = v[idx].second;
	}

	cout << ans << '\n';
}