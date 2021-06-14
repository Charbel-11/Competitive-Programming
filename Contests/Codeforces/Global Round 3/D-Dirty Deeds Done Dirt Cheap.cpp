#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n;
	cin >> n;

	vector<pair<pair<int, int>, int>> inc;
	vector<pair<pair<int,int>, int>> dec;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		if (a < b) {
			inc.push_back({ {a,b}, i + 1 });
		}
		else {
			dec.push_back({ {a,b}, i + 1 });
		}
	}

	if (inc.size() > dec.size()) {
		cout << inc.size() << endl;

		sort(inc.rbegin(), inc.rend());
		for (int i = 0; i < inc.size(); i++) {
			cout << inc[i].second << " ";
		}
		cout << endl;
	}
	else {
		cout << dec.size() << endl;

		sort(dec.begin(), dec.end());
		for (int i = 0; i < dec.size(); i++) {
			cout << dec[i].second << " ";
		}
		cout << endl;
	}
}