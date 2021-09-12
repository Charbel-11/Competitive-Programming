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

	vector<int> P(26);
	for (auto& x : P) { cin >> x; }

	for (auto& x : P) {
		cout << (char)('a' + x - 1);
	}
	cout << '\n';
}