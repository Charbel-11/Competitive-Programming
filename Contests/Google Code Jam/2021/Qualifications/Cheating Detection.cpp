#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream cin("c.txt");

	int t, p; cin >> t >> p;
	int n = 100, m = 10000;
	for (int qq = 1; qq <= t; qq++) {
		vector<string> grid(n); for (auto& s : grid) { cin >> s; }
		
		vector<double> weight(m);
		for (int j = 0; j < m; j++){
			for (int i = 0; i < n; i++) {
				weight[j] += (grid[i][j] == '1');
			}
			weight[j] = log2(n/ weight[j]);
		}

		multiset<double> w;
		for (int i = 0; i < m; i++) { w.insert(weight[i]); }
		for (int i = 0; i < n; i++) { w.erase(w.begin()); }
		double threshold = *w.begin();

		vector<pair<double, int>> prob(n);
		for (int i = 0; i < n; i++) {
			double cur = 0;
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == '0') { 
					if (weight[j] < threshold) { cur += 1; }
				}
				else { cur += weight[j]; }
			}
			prob[i] = { cur,i };
		}
		sort(prob.rbegin(), prob.rend());

		for (int i = 0; i < n; i++) { cout << prob[i].first << '\n'; }

		cout << "Case #" << qq << ": " << prob[0].second + 1 << '\n';
	}
}