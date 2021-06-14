#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> nums(n); for (auto &x : nums) { cin >> x; }

	map<int, int> freq; int rep = 0;
	for (auto x : nums) {
		freq[x]++;
		if (freq[x] > 1) { rep++; }
	}

	if (rep == 0) { cout << 0 << endl; return 0; }

	int answ = n;
	for (int i = 0; i < n; i++) {
		int curRep = rep; map<int, int> curFreq = freq;
		for (int j = i; j < n; j++) {
			if (curFreq[nums[j]] > 1) { curFreq[nums[j]]--; curRep--; }
			if (curRep == 0) { answ = min(answ, j - i + 1); break; }
		}
	}

	cout << answ << endl;
}