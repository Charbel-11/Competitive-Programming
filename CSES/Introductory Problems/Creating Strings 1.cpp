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
	sort(s.begin(), s.end());
	vector<string> res;
	do{
		res.push_back(s);
	} while (next_permutation(s.begin(), s.end()));

	cout << res.size() << '\n';
	for (auto &s : res) { cout << s << '\n'; }
}