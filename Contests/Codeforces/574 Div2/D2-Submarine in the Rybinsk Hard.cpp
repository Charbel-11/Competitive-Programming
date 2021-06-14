#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const long long mod = 998244353;
long long n;
long long pow10[22];
vector<int> bigOrEq;
vector<int> sizeFreq;

long long cont(string num) {
	long long added = 0;
	long long curAdded = 0;
	int s = num.size();
	for (int i = 0; i < 2 * s; i++) {
		curAdded += (num[s - 1 - i / 2] - '0') * pow10[i];
		curAdded %= mod;
	}
	curAdded *= bigOrEq[num.size()];
	curAdded %= mod;
	
	added += curAdded;

	for (int i = num.size() - 1; i >= 1; i--) {
		curAdded = 0;

		int times = sizeFreq[i];

		for (int j = 0; j < 2 * i; j++) {
			curAdded += (num[s - 1 - j / 2] - '0') * pow10[j];
			curAdded %= mod;
		}

		int numPos = i;
		for (int j = 2 * i; j < s + i; j++) {
			curAdded += (num[s - 1 - numPos] - '0') * pow10[j] * 2;
			numPos++;
			curAdded %= mod;
		}

		curAdded *= times;
		curAdded %= mod;

		added += curAdded;
		added %= mod;
	}

	return added;
}

int main() {
	cin >> n;

	vector<string> nums(n);
	sizeFreq.resize(11);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		sizeFreq[nums[i].size()]++;
	}

	bigOrEq.resize(11, 0);
	for (int i = 1; i < 11; i++) {
		bigOrEq[1] += sizeFreq[i];
	}
	for (int i = 2; i < 11; i++) {
		bigOrEq[i] = bigOrEq[i - 1] - sizeFreq[i - 1];
	}

	pow10[0] = 1;
	for (int i = 1; i < 22; i++) {
		pow10[i] = (pow10[i - 1] * 10) % mod;
	};

	long long res = 0;
	for (int i = 0; i < n; i++) {
		res += cont(nums[i]);
		res %= mod;
	}

	cout << res << endl;
}