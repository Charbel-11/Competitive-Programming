#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	int me;
	cin >> me;
	int seats = me;

	vector<int> others(n - 1);
	for (int i = 0; i < n - 1; i++) {
		cin >> others[i];
		seats += others[i];
	}

	vector<int> answ;
	answ.push_back(1);
	int curS = me;

	for (int i = 0; i < n - 1; i++) {
		if (me >= 2 * others[i]) {
			curS += others[i];
			answ.push_back(i + 2);
		}
	}

	if (curS > seats / 2) {
		cout << answ.size() << endl;
		for (int i = 0; i < answ.size(); i++) {
			cout << answ[i] << " ";
		}
		cout << endl;
	}
	else {
		cout << 0 << endl;
	}
}