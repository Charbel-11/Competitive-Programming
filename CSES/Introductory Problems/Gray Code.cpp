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
	vector<string> codes = { "0","1" };
	for (int i = 1; i < n; i++) {
		vector<string> newCodes;
		for (auto& s : codes) { newCodes.push_back('0' + s); }
		reverse(codes.begin(), codes.end());
		for (auto& s : codes) { newCodes.push_back('1' + s); }
		swap(codes, newCodes);
	}

	for (auto& s : codes) { cout << s << '\n'; }
}