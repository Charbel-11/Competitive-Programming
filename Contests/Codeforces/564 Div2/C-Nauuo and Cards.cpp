#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	int n;
	cin >> n;

	bool rotated = false;
	bool startCheckRot = false;
	int c = 1;
	map<int, int> hand;
	map<int, int> pile;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		hand.insert({ t, i + 1 });
	}
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		
		pile.insert({ t,i + 1 });
		if (startCheckRot && t == c) {
			c++;
		}
		else if (startCheckRot && t != c) {
			rotated = false;
			startCheckRot = false;
		}
		else if (t == 1) {
			startCheckRot = true;
			rotated = true;
			c++;
		}
	}
	if (rotated && (c>n || hand.count(c)!=0)) {
		c--;

		map<int, int>::iterator itr = pile.begin();
		while (itr != pile.end() && (itr->first <= c)) {
			itr++;
		}

		while (itr != pile.end()) {
			if (itr->second >= itr->first - c) {
				rotated = false;;
			}
			itr++;
		}

		if (rotated) {
			cout << pile[1] - 1 << endl;
			return 0;
		}
	}

	int res = n;
	int toRem = 0;
	map<int, int>::iterator itr = pile.begin();
	while (itr != pile.end()) {
		if (itr->first != 0 && itr->second >= itr->first) {
			int tem = itr->second + 1 - itr->first;
			if (tem > toRem) {
				toRem = tem;
			}
		}
		itr++;
	}
	res += toRem;
	cout << res << endl;
}