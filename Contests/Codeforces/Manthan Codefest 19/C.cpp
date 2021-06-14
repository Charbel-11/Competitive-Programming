#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n;

int highestPow(int n) {
	int res = 1; int pow = 0;
	while (res <= n) {
		res *= 2; pow++;
	}
	
	return pow - 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n;

	vector<vector<int>> nums(n); for (int i = 0; i < n; i++) { nums[i].resize(n); }

	int pow = highestPow(n); int count = 0;
	int limit = 0; int limit2 = 1 << pow;
	while (limit2 != n) {
		for (int i = 0; i < n; i++)
			for (int j = limit; j < limit2; j++)
				nums[i][j] = count++;

		limit = limit2;
		pow = highestPow(n - limit);
		limit2 = 1 << pow; limit2 += limit;
	}

	for (int i = 0; i < n; i++)
		for (int j = limit; j < limit2; j++) 
			nums[i][j] = count++;
	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << nums[i][j] << " ";
		}
		cout << endl;
	}
	
	/* //To test
	for (int i = 0; i < n; i++) {
		int res = nums[i][0];
		int res2 = nums[0][i];
		for (int j = 1; j < n; j++) {
			res = res ^ nums[i][j];
			res2 = res2 ^ nums[j][i];
		}
		
		if (res != 0 || res2 != 0) { cout << "Eee" << endl; }

	}*/
}