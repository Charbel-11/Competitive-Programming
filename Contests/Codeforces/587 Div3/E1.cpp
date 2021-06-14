#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int q; cin >> q;

	ll checkPoint[5] = { 0,45,9045,1395495,41938884};
	ll start[5] = { 0, 11, 192, 2893};
	ll rate[5] = { 1, 2, 3, 4, 5 };

	for (int z = 0; z < q; z++) {
		ll k; cin >> k;

		int i = 1;
		while (i != 5 && k > checkPoint[i]) { i++; }
		k -= checkPoint[i - 1];

		ll number = pow(10, i-1);
		ll cur = start[i - 1];
		while (k > cur) {
			k -= cur;
			cur += rate[i - 1];
			number++;
		}

		vector<ll> temp;
		for (int i = 1; i <= number; i++) {
			if (i < 10) { temp.push_back(i); }
			else if (i < 100) { temp.push_back(i / 10); temp.push_back(i % 10); }
			else if (i < 1000) {
				temp.push_back(i / 100);
				temp.push_back((i%100) / 10);
				temp.push_back(i % 10);
			}
			else if (i < 10000){
				temp.push_back(i / 1000);
				temp.push_back((i % 1000) / 100);
				temp.push_back((i % 100) / 10);
				temp.push_back(i % 10);
			}
			else {
				temp.push_back(i / 10000);
				temp.push_back((i % 10000) / 1000);
				temp.push_back((i % 1000) / 100);
				temp.push_back((i % 100) / 10);
				temp.push_back(i % 10);
			}
		}

		cout <<"AA"<< temp[k-1] << endl;
	}
}