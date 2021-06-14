#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	long long n, k;
	int m;
	cin >> n >> m >> k;

	vector<long long> specNums(m);
	for (int i = 0; i < m; i++) {
		cin >> specNums[i];
	}

	int specIndex = 0;
	long long res = 0;
	int skipped = 0;
	long long i = 1;

	while (specIndex < m) {
		long long range = k*i + skipped;

		bool didsmthg = false;
		while (specIndex < m && specNums[specIndex] <= range) {
			specIndex++;
			skipped++;
			didsmthg = true;
		}
		res += didsmthg;

		if (!didsmthg) { 
			i = (specNums[specIndex] - skipped) / k; 
			if ((specNums[specIndex] - skipped) % k != 0) {
				i++;
			}
		}
	}

	cout << res << endl;
	return 0;
}