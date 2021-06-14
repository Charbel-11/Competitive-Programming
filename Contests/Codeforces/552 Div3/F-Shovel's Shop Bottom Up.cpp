#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
	int n, numOffers, numToBuy;
	vector<int> shovels;
	vector<pair<int, int>> sO;

	cin >> n >> numOffers >> numToBuy;

	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		shovels.push_back(t);
	}
	sort(shovels.begin(), shovels.end());

	for (int i = 0; i < numOffers; i++) {
		int t1, t2;
		cin >> t1 >> t2;

		if (t1 <= numToBuy) {
			sO.push_back({ t1,t2 });	//push only usable offers
		}
	}
	sort(sO.begin(), sO.end());

	vector<int> minC(numToBuy + 1, INT_MAX);

	vector<int> partSum(numToBuy + 1);		//represents partial sum from 0 to i
	partSum[0] = shovels[0];
	for (int i = 1; i < numToBuy + 1; i++) {
		partSum[i] = partSum[i - 1] + shovels[i - 1];
	}

	minC[0] = 0;
	for (int i = 0; i < numToBuy; i++) {
		minC[i + 1] = min(minC[i + 1], minC[i] + shovels[i]);

		for (int z = 0; z < sO.size(); z++) {
			int j = sO[z].first;
			if (i + j <= numToBuy) {
				minC[i + j] = min(minC[i + j], minC[i] + partSum[i + j] - partSum[i + sO[z].second]);
			}
			else {
				break;
			}
		}
	}

	cout << minC[numToBuy] << endl;
}