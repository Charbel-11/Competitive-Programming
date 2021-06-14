#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

long long DP[200004][4];		//T0 or T1
multimap<long long, long long> treasures;
set<long long> safeCol;
int n, m, treasN, safeColN;

long long minMoves(int row, int T) {		//T: ll, lr, rl, rr
	if (DP[row][T] != -1) { return DP[row][T]; }
	if (row > n) { return 0; }
	if (treasures.count(row) == 0) {
		if (treasures.lower_bound(row) == treasures.end()) { return -1ll; }
		return 1 + minMoves(row + 1, T); 
	}

	//prev
	int rowT = row - 1;
	multimap<long long, long long>::iterator itr = treasures.find(rowT);
	while (itr == treasures.end()) { rowT--; itr = treasures.find(rowT); }

	long long T0 = itr->second;		//leftmost T
	long long T1 = itr->second;		//rightmost T
	while (itr != treasures.end() && itr->first == rowT) {
		if (itr->second > T1) { T1 = itr->second; }
		if (itr->second < T0) { T0 = itr->second; }
		itr++; 
	}

	set<long long>::iterator itr2 = safeCol.lower_bound(T0);
	long long lr = -1;	if (itr2 != safeCol.end()) { lr = *itr2; }
	long long ll = -1;	if (itr2 != safeCol.begin()) { ll = *prev(itr2); }

	itr2 = safeCol.lower_bound(T1);
	long long rr = -1;	if (itr2 != safeCol.end()) { rr = *itr2; }
	long long rl = -1;	if (itr2 != safeCol.begin()) { rl = *prev(itr2); }


	//cur
	itr = treasures.find(row);
	long long T0C = itr->second;		//leftmost T
	long long T1C = itr->second;		//rightmost T
	while (itr != treasures.end() && itr->first == row) {
		if (itr->second > T1C) { T1C = itr->second; }
		if (itr->second < T0C) { T0C = itr->second; }
		itr++;
	}

	itr2 = safeCol.lower_bound(T0C);
	long long lrC = -1;	if (itr2 != safeCol.end()) { lrC = *itr2; }
	long long llC = -1;	if (itr2 != safeCol.begin()) { llC = *prev(itr2); }

	itr2 = safeCol.lower_bound(T1C);
	long long rrC = -1;	if (itr2 != safeCol.end()) { rrC = *itr2; }
	long long rlC = -1;	if (itr2 != safeCol.begin()) { rlC = *prev(itr2); }

	long long res = 0;

	long long curPos;
	if (T == 0) { curPos = ll; }
	else if (T == 1) { curPos = lr; }
	else if (T == 2) { curPos = rl; }
	else { curPos = rr; }

	long long c1, c2;

	if (row == n) {
		c1 = llabs(T1C - curPos) + llabs(T1C - T0C);
		c2 = llabs(T0C - curPos) + llabs(T1C - T0C);
		DP[row][T] = c1 > c2 ? c2 : c1;

		return DP[row][T];
	}

	if (llC == -1) { c1 = LLONG_MAX; }
	else { c1 = llabs(T1C - curPos) + llabs(T1C - T0C) + llabs(T0C - llC) + minMoves(row + 1, 0) + 1; }
	if (lrC == -1) { c2 = LLONG_MAX; }
	else { c2 = llabs(T1C - curPos) + llabs(T1C - T0C) + llabs(T0C - lrC) + minMoves(row + 1, 1) + 1; }
	if (c1 > c2) { c1 = c2; }
	if (rlC == -1) { c2 = LLONG_MAX; }
	else { c2 = llabs(T0C - curPos) + llabs(T1C - T0C) + llabs(T1C - rlC) + minMoves(row + 1, 2) + 1; }
	if (c1 > c2) { c1 = c2; }
	if (rrC == -1) { c2 = LLONG_MAX; }
	else { c2 = llabs(T0C - curPos) + llabs(T1C - T0C) + llabs(T1C - rrC) + minMoves(row + 1, 3) + 1; }
	if (c1 > c2) { c1 = c2; }

	res += c1;

	DP[row][T] = res;
	return res;
}

void resetDP() {
	for (int i = 0; i < 200004; i++) {
		for (int j = 0; j < 4; j++) {
			DP[i][j] = -1ll;
		}
	}
}

int main() {
	cin >> n >> m >> treasN >> safeColN;
	resetDP();

	bool here = false;
	for (int i = 0; i < treasN; i++) {
		long long x, y;
		cin >> x >> y;
		if (x == 1 && y == 1)here = true;
		treasures.insert({ x, y });		//x is the row, y column
	}
	if (!here)	treasures.insert({ 1, 1 });
	for (int i = 0; i < safeColN; i++) {
		int temp;
		cin >> temp;
		safeCol.insert(temp);
	}

	multimap<long long, long long>::iterator itr = treasures.find(1);
	long long T0 = itr->second;		//leftmost T
	long long T1 = itr->second;		//rightmost T
	while (itr != treasures.end() && itr->first == 1) {
		if (itr->second > T1) { T1 = itr->second; }
		if (itr->second < T0) { T0 = itr->second; }
		itr++;
	}

	set<long long>::iterator itr2 = safeCol.lower_bound(T0);
	long long lr = -1;	if (itr2 != safeCol.end()) { lr = *itr2; }
	long long ll = -1;	if (itr2 != safeCol.begin()) { ll = *prev(itr2); }
	itr2 = safeCol.lower_bound(T1);
	long long rr = -1;	if (itr2 != safeCol.end()) { rr = *itr2; }
	long long rl = -1;	if (itr2 != safeCol.begin()) { rl = *prev(itr2); }


	long long c1, c2;
	if (ll == -1) { c1 = LLONG_MAX; }
	else { c1 = llabs(T1 - 1) + llabs(T1 - T0) + llabs(T0 - ll) + minMoves(2, 0) + 1; }
	if (lr == -1) { c2 = LLONG_MAX; }
	else { c2 = llabs(T1 - 1) + llabs(T1 - T0) + llabs(T0 - lr) + minMoves(2, 1) + 1; }
	if (c1 > c2) { c1 = c2; }
	if (rl == -1) { c2 = LLONG_MAX; }
	else { c2 = llabs(T0 - 1) + llabs(T1 - T0) + llabs(T1 - rl) + minMoves(2, 2) + 1; }
	if (c1 > c2) { c1 = c2; }
	if (rr == -1) { c2 = LLONG_MAX; }
	else { c2 = llabs(T0 - 1) + llabs(T1 - T0) + llabs(T1 - rr) + minMoves(2, 3) + 1; }
	if (c1 > c2) { c1 = c2; }

	cout << c1 << endl;
}
