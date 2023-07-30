#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		vector<string> grid(8);
        for(auto &s : grid){ cin >> s; }
        int startI = -1, startJ = -1;
        for(int i = 7; i >= 0; i--){
            for(int j = 0; j < 8; j++){
                if (grid[i][j] != '.') {
                    startI = i;
                    startJ = j;
                    break;
                }
            }
            if (startI != -1){ break; }
        }

        string ans = "";
        while(startI >= 0 && grid[startI][startJ] != '.'){
            ans.push_back(grid[startI][startJ]);
            startI--;
        }

        reverse(ans.begin(), ans.end());
        cout << ans << '\n';
	}
}