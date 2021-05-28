//https://www.spoj.com/problems/KPMATRIX/

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct FT {
	int n;
	vector<int> vals;
	FT(const int n) :
		n(n), vals(vector<int>(n + 1, 0)) {
	}

	//Adds x
	void update(int i, const int x=1) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	int query(int i) const { // sum from 0 ... i
		int sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
	int query(int i, int j) const {		// sum from i ... j
		return query(j) - query(i - 1);
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m, 0));
	vector<vector<int>> below(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
			below[i][j] = (i ? below[i - 1][j] : 0) + grid[i][j];
		}

	int A, B; cin >> A >> B;	

	long long res = 0;
	for (int i1 = 0; i1 < n; i1++) {
		for (int i2 = i1; i2 < n; i2++) {
			int cur = 0;
			vector<int> prefixes; prefixes.push_back(0);
			for (int k = 0; k < m; k++) {
				cur += below[i2][k] - (i1 ? below[i1 - 1][k] : 0);
				prefixes.push_back(cur);
			}
			sort(prefixes.begin(), prefixes.end());
			prefixes.erase(unique(prefixes.begin(), prefixes.end()), prefixes.end());

			cur = 0; 
			FT tree(prefixes.size() + 1);
			int pos0 = lower_bound(prefixes.begin(), prefixes.end(), 0) - prefixes.begin();
			tree.update(pos0);
			for (int k = 0; k < m; k++) {
				cur += below[i2][k] - (i1 ? below[i1 - 1][k] : 0);
				int low = cur - B, high = cur - A;
				int l = lower_bound(prefixes.begin(), prefixes.end(), low) - prefixes.begin();
				int r = upper_bound(prefixes.begin(), prefixes.end(), high) - prefixes.begin() - 1;
				if (l <= r) { res += tree.query(l, r); }

				int curPos = lower_bound(prefixes.begin(), prefixes.end(), cur) - prefixes.begin();
				tree.update(curPos);
			}	
		}
	}

	cout << res << '\n';
}