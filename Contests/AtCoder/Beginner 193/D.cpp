#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll countScore(string& s) {
	vector<int> freq(10, 0);
	for (int i = 0; i < 5; i++) { freq[s[i] - '0']++; }

	ll ans = 0;
	for (int i = 1; i < 10; i++) {
		ll curP = 1;
		while (freq[i]--) { curP *= 10; }
		ans += curP * i;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int K; cin >> K;
	string s, t; cin >> s >> t;

	double ans = 0;
	vector<int> freq(10, K);
	
	for (int i = 0; i < 4; i++) { freq[s[i] - '0']--; freq[t[i] - '0']--; }
	ll available = 9ll * K - 8;

	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			if (freq[i] == 0 || freq[j] == 0 || (freq[i] == 1 && i == j)) { continue; }
			s[4] = '0' + i; t[4] = '0' + j;
			if (countScore(s) <= countScore(t)) { continue; }

			double curP = (double) freq[i] / available;
			freq[i]--; 
			curP *= (double) freq[j] / (available - 1);
			freq[i]++;
			ans += curP;
		}
	}

	cout << setprecision(6) << fixed << ans << '\n';
}