#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;

	vector<int> nums(n);
	int neg = 0; long long dif = 0; bool zero = false;

	for (int i = 0; i < n; i++) {
		long long temp; cin >> temp;
		if (temp < 0) { neg++; }
		if (temp == 0) { dif++; zero = true; }
		else { dif += abs(temp) - 1; }
	}
	
	long long res = dif;
	if (neg % 2 && !zero) {
		res += 2;
	}

	cout << res << endl;
}