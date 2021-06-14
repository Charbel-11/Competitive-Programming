#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<string> cards(n);
	for (auto &x : cards) { cin >> x; }

	sort(cards.begin(), cards.end());

	long long res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			string first = cards[i], second = cards[j];
			string cur = "";
			for (int l = 0; l < k; l++) {
				if (cards[i][l] == cards[j][l]) { cur.push_back(cards[i][l]); continue; }
				char cur1 = cards[i][l], cur2 = cards[j][l];
				if (cur1 > cur2) { swap(cur1, cur2); }
				//E S T
				if (cur1 == 'E' && cur2 == 'S') { cur.push_back('T'); }
				else if (cur1 == 'E' && cur2 == 'T') { cur.push_back('S'); }
				else if (cur1 == 'S' && cur2 == 'T') { cur.push_back('E'); }
			}

			if (binary_search(cards.begin() + 1+ j, cards.end(), cur)) {
				res++;
			}
		}
	}

	cout << res << endl;
}