#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int n; cin >> n;
	string s; cin >> s;
	int first = 0, second = 0, missingFirst = 0, missingSecond = 0;

	for (int i = 0; i < n; i++) {
		if (i < n / 2) {
			if (s[i] == '?') { missingFirst++; }
			else { first += s[i] - '0'; }
		}
		else {
			if (s[i] == '?') { missingSecond++; }
			else { second += s[i] - '0'; }
		}
	}

	if (missingFirst == 0 && missingSecond == 0) {
		if (first == second) { cout << "Bicarp" << endl; }
		else { cout << "Monocarp" << endl; }
		return 0;
	}

	if (missingSecond > missingFirst) {
		swap(missingFirst, missingSecond);
		swap(first, second);
	}
	missingFirst -= missingSecond;
	int dif = first - second;
	if (dif > 0) { cout << "Monocarp" << endl; return 0; }
	dif = -dif;

	int mMoves = (missingFirst + 1) / 2;
	int bMoves = missingFirst - mMoves;

	if (mMoves * 9 > dif || bMoves * 9 < dif || (mMoves - bMoves)) { cout << "Monocarp" << endl; return 0; }
	cout << "Bicarp" << endl;
}