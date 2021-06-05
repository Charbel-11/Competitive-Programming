#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, ans; cin >> n >> ans;
	vector<bitset<30>> nums;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		nums.push_back(bitset<30>(s));
	}

	for (int i = 0; i < n; i++) 
		for (int j = i + 1; j < n; j++) 
			ans = min(ans, (int)(nums[i] ^ nums[j]).count());
		
	cout << ans << '\n';
}