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

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		string s; cin >> s;

		int sheeps = 0; 
		for (auto& c : s) { sheeps += (c == '*'); }

		vector<ll> leftSteps;
		ll curPos = 0, ans = 0, sheepsR = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '*'){
				if (curPos != i) { leftSteps.push_back(i - curPos); ans += i - curPos; }
				else { sheepsR++; }
				curPos++;
			}
		}

		reverse(leftSteps.begin(), leftSteps.end());
		ll prevAns = ans;
		for (int i = 1; i <= n - sheeps; i++) {
			ll curAns = prevAns + sheepsR - leftSteps.size();
			while (!leftSteps.empty() && leftSteps.back() == i) { leftSteps.pop_back(); sheepsR++; }

			ans = min(ans, curAns);
			prevAns = curAns;
		}

		cout << ans << '\n';
	}
}
