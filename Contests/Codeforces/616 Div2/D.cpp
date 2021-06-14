#include <iostream>
#include <vector>
#include <string>

using namespace std;

string s;
vector<vector<int>> freq;

bool query(int l, int r) {
	if (l == r || s[l] != s[r]) { return true; }

	int distinct = 0;
	for(int i = 0; i < 26; i++){
		int curFreq = freq[r][i] - freq[l][i];		//No need to include freq[l] since we know s[l] = s[r] -> s[r] is counted as distinct letter
		if (curFreq) { distinct++; }
	}

	return distinct > 2;
}

int main() {
	cin >> s;
	int q; cin >> q;

	freq.resize(s.size());
	for (int i = 0; i < s.size(); i++) {
		freq[i].resize(26, 0);
		if (i) {
			for (int k = 0; k < 26; k++)
				freq[i][k] = freq[i - 1][k];
		}
		freq[i][s[i] - 'a']++;
	}

	while (q--) {
		int l, r; cin >> l >> r; l--; r--;

		cout << (query(l, r) ? "Yes" : "No") << endl;
	}
}