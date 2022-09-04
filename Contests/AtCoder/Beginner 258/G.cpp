#include <iostream>
#include <string>
#include <map>
#include <set>
#include <bitset>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<string> A(n); for (auto& s : A) { cin >> s; }
	vector<bitset<3001>> Abit;
	for (int i = 0; i < n; i++) { Abit.emplace_back(A[i]); }

	ll ans = 0;
	for(int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (A[i][j] == '0') { continue; }
			auto AND = Abit[i] & Abit[j];
			ans += AND.count();
		}
	}

	cout << ans / 3 << '\n';
}
