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

	int T; cin >> T;
	while (T--) {
		int n; cin >> n;
		vector<pair<ll, ll>> commands(n);
		for (auto& p : commands) { cin >> p.first >> p.second; }
		commands.push_back({ 1e12, 0 });

		int ans = 1; bool removed = false;
		ll t = commands[0].first, s = 0, e = commands[0].second;
		for (int i = 1; i < n; i++) {
			ll nextT = commands[i].first;
			ll diff = nextT - t;
			if (abs(e - s) <= diff) { 
				ans++; t = nextT;
				s = e; e = commands[i].second;
				removed = false;
				continue;
			}
			if (!removed) { ans--; removed = true; }
			if (e > s && (commands[i].second < s || commands[i].second > e)) { continue; }
			else if (e <= s && (commands[i].second > s || commands[i].second < e)) { continue; }

			ll cur = s;
			if (e > s) { 
				cur += diff;
				if (cur > commands[i].second) { continue; }
			}
			else {
				cur -= diff;
				if (cur < commands[i].second) { continue; }
			}

			ll totalTime = commands[i + 1].first - t;
			cur = s;
			if (e > s) {
				cur += totalTime;
				if (cur < commands[i].second) { continue; }
			}
			else {
				cur -= totalTime;
				if (cur > commands[i].second) { continue; }
			}

			ans++;
		}

		cout << ans << '\n';
	}
}