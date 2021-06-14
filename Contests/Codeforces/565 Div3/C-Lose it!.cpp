#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

int main() {
	int n;
	cin >> n;

	int mapp[43];
	mapp[4] = 0; mapp[8] = 1; mapp[15] = 2; mapp[16] = 3; mapp[23] = 4; mapp[42] = 5;
	vector<int> specNum(6, 0);
	int res = 0;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;

		if (mapp[temp] == 0) {
			specNum[0]++;
		}
		else {
			if (specNum[mapp[temp] - 1] == 0) {
				res++;
			}
			else {
				specNum[mapp[temp] - 1]--;
				specNum[mapp[temp]]++;
			}
		}
	}
	for (int i = 1; i < 6; i++) {
		res += i * specNum[i - 1];
	}

	cout << res << endl;
}