#include <bits/stdc++.h>
using namespace std;

//For each i in the returned vector, the number represents the length of
//the longest proper prefix equal to the suffix ending at index i, both in the substring s[0..i]
//Proper prefix means prefix != string
vector<int> prefixFunction(string& s) {
	vector<int> pf(s.size(), 0);
	for (int i = 1; i < s.size(); i++) {
		int j = pf[i - 1];
		while (j > 0 && s[j] != s[i]) { j = pf[j - 1]; }
		if (s[j] == s[i]) { j++; }
		pf[i] = j;
	}
	return pf;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int n; cin >> n;
    vector<string> v(n); int totalLen = 0;
    for(auto& s : v){ cin >> s; totalLen += s.size(); }
    vector<vector<int>> savedLetters(n, vector<int>(n, 0));
    vector<bool> skip(n, false);

    for(int i = 0; i < n; i++){
        vector<int> indices(n, -1);
        string curFullStr = v[i];
        for(int j = 0; j < n; j++){
            if (j == i) { continue; }
            curFullStr += v[j];
            indices[j] = curFullStr.size() - 1;
        }
        auto prefFunc = prefixFunction(curFullStr);

        int idx = 0, curLen = 0;
        if (i == 0){ idx = 1; }
        for(int j = v[i].size(); j < curFullStr.size(); j++){
            curLen++;
            if (prefFunc[j] >= v[i].size() && curLen >= v[i].size()){
                if (!(v[i].size() == v[idx].size() && idx < i)) {
                    skip[i] = true; break;
                }
            }
            if (j == indices[idx]){
                savedLetters[idx][i] = prefFunc[j];
                idx++; if (idx == i){ idx++; }
                curLen = 0;
            }
        }
    }

    int alwaysOne = 0;
    for(int i = 0; i < n; i++){
        if (skip[i]){ alwaysOne |= (1 << i); }
    }
    vector<vector<int>> dp(1 << n, vector<int>(n, totalLen));
    for(int i = 0; i < n; i++){ dp[(1 << i) | alwaysOne][i] = v[i].size(); }
    for(int i = 1; i < (1<<n); i++){
        i = i | alwaysOne;
        for(int j = 0; j < n; j++){
            if (skip[j]){ continue; }
            if ((i & (1 << j)) == 0){ continue; }
            for(int k = 0; k < n; k++){
                if (skip[k]){ continue; }
                if ((i & (1 << k)) != 0){ continue; }
                int newMask = i + (1 << k);
                dp[newMask][k] = min(dp[newMask][k], dp[i][j] + (int)v[k].size() - savedLetters[j][k]);
            }
        }
    }

    cout << *min_element(dp[(1<<n)-1].begin(), dp[(1<<n)-1].end()) << '\n';
}