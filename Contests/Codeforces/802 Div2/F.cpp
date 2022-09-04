#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<vector<int>> grid1(2, vector<int>(n));
    vector<vector<int>> grid2(2, vector<int>(n));
    for(auto &v : grid1)
        for(auto &x : v)
            cin >> x;
    for(auto &v : grid2)
        for(auto &x : v)
            cin >> x;

    int diff1 = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            diff1 += grid1[i][j] == 1;
            diff1 -= grid2[i][j] == 1;
        }
    }
    if (diff1 != 0){ cout << -1 << '\n'; return 0 ;}

    int row1Diff = 0, row2Diff = 0;
    ll ans = 0;
    for(int j = 0; j < n; j++){
        row1Diff += (grid1[0][j] == 1) - (grid2[0][j] == 1);
        row2Diff += (grid1[1][j] == 1) - (grid2[1][j] == 1);

        if (row1Diff > 0 && row2Diff < 0){
            row1Diff--; row2Diff++;
            ans++;
        }
        else if (row1Diff < 0 && row2Diff > 0){
            row1Diff++; row2Diff--;
            ans++;
        }

        ans += abs(row1Diff) + abs(row2Diff);
    }

    cout << ans << '\n';
}