#include <iostream>
#include <string>
#include <vector>

using namespace std;

int maxIdx(int num) {
	int ans = 0;
	while (num) { ans++; num /= 2; }
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		cout << "Case #" << q << ": " << endl;
		int N; cin >> N;
		int ones = maxIdx(N), countedOnes = 0, i = 1;
		int target = N - ones; bool left = true;

		while (target) {
			if (target & 1) {
				if (left) {
					for (int l = 1; l <= i; l++) { cout << i << " " << l << endl; }
				}
				else {
					for (int l = i; l > 0; l--) { cout << i << " " << l << endl; }
				}
				left = !left; i++;
			}
			else {
				cout << i << " " << (left ? 1 : i) << endl; i++; countedOnes++;
			}
			target /= 2;
		}
		ones -= countedOnes;
		while (ones--) { cout << i << " " << (left ? 1 : i) << endl; i++; }
	}
}