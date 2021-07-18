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

	vector<int> maxVal;
	int cur = 1, curS = 1; 
	while (curS <= 5000) {
		maxVal.push_back(curS); 
		cur += 2; curS += cur;
	}

	int t; cin >> t;
	while (t--) {
		int s; cin >> s;
		cout << lower_bound(maxVal.begin(), maxVal.end(), s) - maxVal.begin() + 1 << '\n';
	}
}