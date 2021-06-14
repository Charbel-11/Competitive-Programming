#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int T, F; cin >> T >> F;

	while (T--) {
		vector<bool> used(6, 0);
		vector<vector<int>> startWith(6);
		string ans = "";

		//119 moves
		int counter = 1;
		while (counter <= 595) {
			cout << counter << endl;
			cout.flush();

			char letter; cin >> letter;
			startWith[letter - 'A'].push_back(counter);
			counter += 5;
		}
		int curIdx;
		for (int i = 0; i < 6; i++) {
			if (startWith[i].size() == 23) {
				ans.push_back('A' + i);
				used[i] = 1;
				curIdx = i; break;
			}
		}

		//23 moves
		vector<vector<int>> secondLetter(6);
		for (int i = 0; i < 23; i++) {
			int cur = startWith[curIdx][i] + 1;
			cout << cur << endl;
			cout.flush();

			char letter; cin >> letter;
			secondLetter[letter - 'A'].push_back(cur);
		}
		for (int i = 0; i < 6; i++) {
			if (secondLetter[i].size() == 5) {
				ans.push_back('A' + i);
				used[i] = 1;
				curIdx = i; break;
			}
		}

		//5 moves
		vector<vector<int>> thirdLetter(6);
		for (int i = 0; i < 5; i++) {
			int cur = secondLetter[curIdx][i] + 1;
			cout << cur << endl;
			cout.flush();

			char letter; cin >> letter;
			thirdLetter[letter - 'A'].push_back(cur);
		}
		for (int i = 0; i < 6; i++) {
			if (thirdLetter[i].size() == 1) {
				ans.push_back('A' + i);
				used[i] = 1;
				curIdx = i; break;
			}
		}

		cout << thirdLetter[curIdx][0] + 1 << endl;
		cout.flush();
		char letter; cin >> letter;
		for (int i = 0; i < 6; i++) {
			if (used[i] || (i + 'A') == letter) { continue; }
			ans.push_back(i + 'A'); break;
		}
		ans.push_back(letter);
		cout << ans << endl;
		cout.flush();
		string s; cin >> s;
		if (s == "N") { break; }
	}
}