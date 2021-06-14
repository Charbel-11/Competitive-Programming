#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long n;
long long pow10[22];

long long cont(string num) {
	long long added = 0;

	int s = num.size();
	for (int i = 0; i < 2 * s; i++) {
		added += (num[s-1-i/2] - '0') * pow10[i];
		added %= 998244353;
	}

	return (added*n)%998244353;
}

int main() {
	cin >> n;

	vector<string> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	pow10[0] = 1;
	for (int i = 1; i < 22; i++) {
		pow10[i] = (pow10[i-1] * 10) % 998244353;
	}

	long long res = 0;
	for (int i = 0; i < n; i++) {
		res += cont(nums[i]);
		res %= 998244353;
	}

	cout << res << endl;
}