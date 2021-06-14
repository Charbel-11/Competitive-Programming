#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	vector<vector<pair<int, int>>> answ(n);

	for (int i = 0; i < n-1; i++) {
		answ[i].push_back({ nums[i], 0 });

		bool candy = (nums[i] + nums[i + 1]) >= 10;
		int newNum = (nums[i] + nums[i + 1]) % 10;
		answ[i].push_back({ newNum, candy });
	}
	answ[n - 1].push_back({ nums[n - 1], 0 });

	int power = 2;
	int maxPower = log2(n);

	while (power <= maxPower) {
		int curP = pow(2, power);
		for (int i = 0; i + curP/2 < n; i++) {
			bool candy = (answ[i][answ[i].size() - 1].first + answ[i + curP/2][answ[i + curP/2].size() - 1].first) >= 10;
			int newNum = (answ[i][answ[i].size() - 1].first + answ[i + curP/2][answ[i + curP/2].size() - 1].first) % 10;

			answ[i].push_back({ newNum, candy + answ[i][answ[i].size() - 1].second + answ[i + curP / 2][answ[i + curP / 2].size() - 1].second });
		}

		power++;
	}

	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;

		if (l == r) { cout << 0 << endl; continue; }

		int p = log2(r - l + 1);

		cout << answ[l - 1][p].second << endl;
	}
	
}