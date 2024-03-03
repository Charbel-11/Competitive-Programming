#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    string s; cin >> s;

    vector<vector<int>> colIdx(m);
    vector<int> colors(n);
    for(int i = 0; i < n; i++){
        cin >> colors[i]; colors[i]--;
        colIdx[colors[i]].push_back(i);
    }

    string ans = s;
    map<int, int> seenCol;
    for(int i = 0; i < n; i++){
        seenCol[colors[i]]++;
        int nxtIdx = seenCol[colors[i]] % colIdx[colors[i]].size();
        ans[colIdx[colors[i]][nxtIdx]] = s[i];
    }

    cout << ans << '\n';
}