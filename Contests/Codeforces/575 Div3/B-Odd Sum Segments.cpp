#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int q;
	cin >> q;

	for (int z = 0; z < q; z++) {
		int n, k;
		cin >> n >> k;

		vector<long long> answ;
		vector<long long> nums(n);
		for (int j = 0; j < n; j++) {
			cin >> nums[j];
		}

		long long curSum = 0;
		for (int i = 0; i < n; i++) {
			if (k == 1) {
				while (i < n) {
					curSum += nums[i];
					i++;
				}
				i--;
			}
			else {
				curSum += nums[i];
			}

			if (curSum % 2 == 1) {
				k--;
				answ.push_back(i+1);
				curSum = 0;
			}
		}

		if (k > 0) {
			cout << "NO" << endl;
		}
		else {
			cout << "YES" << endl;
			for (int i = 0; i < answ.size(); i++) {
				cout << answ[i] << " ";
			}
			cout << endl;
		}
	}
}