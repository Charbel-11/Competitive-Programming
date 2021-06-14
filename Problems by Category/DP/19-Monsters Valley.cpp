// https://community.topcoder.com/stat?c=problem_statement&pm=12350

#include <string>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

//DP[i][j] represents the max dread that i can take from 0 to i with j coins
//while beating all the monsters on the way
//-2 means unprocessed while -1 means impossible
long long DP[52][102];  

vector<long> dread = { 200, 107, 105, 206, 307, 400 };
vector<int> price = { 1, 2, 1, 1, 1, 2 };

//Find the max dread possible to get from 0 to i using at most maxPrice coins (including monst i)
//It has to be at least equal to dread[i] otherwise we won't pass the monster
long long maxD(int i, int maxPrice) {
	if (i < 0) { return 0; }
	if (DP[i][maxPrice] != -2) { return DP[i][maxPrice]; }

	long long c1 = maxD(i - 1, maxPrice);
	if (c1 < dread[i]) {
		c1 = -1;
	}
	
	long long c2 = -1;
	if (price[i] <= maxPrice) {
		long long temp = maxD(i - 1, maxPrice - price[i]);
		if (temp != -1) {
			c2 = dread[i] + temp;
		}
	}

	DP[i][maxPrice] = (c1 > c2) ? c1 : c2;
	return DP[i][maxPrice];
}

void resetDP() {
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 102; j++) {
			DP[i][j] = -2;
		}
	}
}

int main() {
	resetDP();

	int res = 0;
	bool found = false;
	
	while (!found) {
		res++;
		long long a = maxD(dread.size()-1, res);
		if (a != -1) { 
			found = true; 
		}
	}

	cout << res << endl;
}