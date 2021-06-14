#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int n;
	cin >> n;

	bool zero = false;
	map<int, int> freq;
	int tSum = 0;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		if (temp > 0) {
			tSum += temp;
		}
		else {
			zero = true;
		}
		if (freq.count(temp) == 0) { freq[temp] = 1; }
		else { freq[temp]++; }
	}

	map<int, int>::iterator itr = freq.begin();
	if (itr->first == 0 && itr->second > 1) {
		tSum = 0;
	}
	int twos = 0;
	while (itr != freq.end()) {
		if (itr->second > 2) {
			cout << "cslnb" << endl;
			return 0;
		}
		else if (itr->second == 2) {
			twos++;
		}
		itr++;

		if (itr != freq.end()) {
			if (itr->second >= 2 && prev(itr)->first == itr->first - 1) {
				cout << "cslnb" << endl;
				return 0;
			}
		}
	}

	if (tSum == 0 || twos > 1) {
		cout << "cslnb" << endl;
		return 0;
	}

	int finalS = n * (n + 1);
	finalS /= 2;

	int dif = tSum - (finalS - n);

	bool TW = true;
	if (dif % 2 == 0) {
		TW = false;
	}

	if (TW) {
		cout << "sjfnb" << endl;
	}
	else {
		cout << "cslnb" << endl;
	}
}