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

	string s = "codeforces";
	ll k; cin >> k;
	vector<int> ans(10, 1); 
	ll ways = 1;

	int i = 0;
	while (ways < k) {
		ways /= ans[i];
		ans[i]++; 
		ways *= ans[i];
		i++; i %= 10;
	}

	for (i = 0; i < 10; i++) {
		for (int j = 0; j < ans[i]; j++) { cout << s[i]; }
	}
	cout << '\n';
}