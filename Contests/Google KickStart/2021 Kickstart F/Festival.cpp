#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int d, n, k; cin >> d >> n >> k;
		vector<pair<int, int>> start, finish;
		for (int i = 0; i < n; i++) {
			int h, s, e; cin >> h >> s >> e; s--;
			start.push_back({ s, h });
			finish.push_back({ e, h });
		}
		sort(start.begin(), start.end());
		sort(finish.begin(), finish.end());

		ll ans = 0, sumTopK = 0;
		multiset<int> topK, other;

		int sIdx = 0, fIdx = 0;
		for (int i = 0; i < d; i++) {
			while (fIdx < finish.size() && finish[fIdx].first == i) {
				int x = finish[fIdx++].second;
				if (other.find(x) != other.end()) {
					other.erase(other.find(x));
				}
				else if (topK.find(x) != topK.end()) {
					sumTopK -= x;
					topK.erase(topK.find(x));

					if (!other.empty()) {
						int curAdd = *other.rbegin();
						other.erase(other.find(curAdd));
						topK.insert(curAdd);
						sumTopK += curAdd;
					}
				}
			}
			while (sIdx < start.size() && start[sIdx].first == i) {
				int x = start[sIdx++].second;
				if (topK.size() < k) { topK.insert(x); sumTopK += x; }
				else if (*topK.begin() < x) {
					topK.insert(x); sumTopK += x;

					int curRem = *topK.begin();
					topK.erase(topK.begin());
					other.insert(curRem);
					sumTopK -= curRem;
				}
				else { other.insert(x); }
			}

			ans = max(ans, sumTopK);
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
