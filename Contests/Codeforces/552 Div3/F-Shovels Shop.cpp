#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> shovels;
vector<pair<int, int>> sO;
int DP[200002];

//DP works here since we can use an offer more than once
int minPrice(int j) {
	if (j < 0) {
		return 0;
	}

	if (DP[j] != -1) { return DP[j]; }

	int minP = INT_MAX;

	//Instead, we could have added the offer 1 0 to sO
	if (sO.size() == 0 || sO[0].first > j + 1) {			//Edge case size==0
		minP = 0;
		for (int z = 0; z < j + 1; z++) {
			minP += shovels[z];
		}

		DP[j] = minP;
		return minP;
	}

	for (int i = 0; i < sO.size(); i++) {
		if (sO[i].first > j + 1) { break; }
	
		int curPrice = 0;

		for (int k = j + 1 - sO[i].first + sO[i].second; k < j + 1; k++) {
			curPrice += shovels[k];				//index k not j
		}

		curPrice += minPrice(j - sO[i].first);
		if (curPrice < minP) {
			minP = curPrice;
		}
	}

	DP[j] = minP;
	return minP;
}

void resetDP() {
	for (int i = 0; i < 200002; i++) {
		DP[i] = -1;
	}
}

int main() {
	resetDP();

	int n, numOffers, numToBuy;
	cin >> n >> numOffers >> numToBuy;

	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		shovels.push_back(t);
	}
	sort(shovels.begin(), shovels.end());

	int j = numToBuy - 1;		//Need to buy evrthg from 0 to j

	for (int i = 0; i < numOffers; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		
		if (t1 <= numToBuy) {
			sO.push_back({ t1,t2 });	//push only usable offers
		}
	}
	sort(sO.begin(), sO.end());

	cout << minPrice(j) << endl;
}