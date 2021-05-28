#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<int> toOrder;
vector<pair<int, int>> allOffers;
int totSum, n, m;

int bSearch(int a, int b) {
	if (a == b) { return a; }

	int curSum = totSum;
	int mid = (a + b) / 2;

	vector<int> last(n, -1);
	for (int i = 0; i < m; i++) {
		if (allOffers[i].first > mid) { continue; }

		int offer = allOffers[i].second; int day = allOffers[i].first;
		last[offer] = max(last[offer], day);
	}

	vector<vector<int>> offersByDay(mid + 1);
	for (int i = 0; i < n; i++) {
		if (last[i] == -1) { continue; }
		offersByDay[last[i]].push_back(i);
	}

	int money = 0;
	for (int i = 0; i <= mid; i++) {
		money++;

		for (auto &x : offersByDay[i]) {
			if (money > toOrder[x]) {
				money -= toOrder[x];
				curSum -= toOrder[x];
			}
			else {
				curSum -= money;
				money = 0;
				break;
			}
		}
	}

	if (money >= 2 * curSum) {
		return bSearch(a, mid);
	}
	return bSearch(mid + 1, b);
}

int main() {
	cin >> n >> m;
	totSum = 0;
	for (int i = 0; i < n; i++) {
		int temp; cin >> temp;
		toOrder.push_back(temp);
		totSum += temp;
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;

		allOffers.push_back({ a,b });
	}

	cout << bSearch(0, int(4e5)) + 1 << endl;
}