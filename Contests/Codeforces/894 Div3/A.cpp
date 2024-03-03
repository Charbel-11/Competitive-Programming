#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, m; cin >> n >> m;
        int state = 0;

        vector<string> grid(n);
        for(auto &s : grid){ cin >> s; }

        for(int j = 0; j < m; j++){
            for(int i = 0; i < n; i++){
                if (state == 0 && grid[i][j] == 'v'){ state++; break; }
                else if (state == 1 && grid[i][j] == 'i') { state++; break; }
                else if (state == 2 && grid[i][j] == 'k') { state++; break; }
                else if (state == 3 && grid[i][j] == 'a') { state++; break; }
            }
        }


        if (state == 4){ cout << "YES\n"; }
        else { cout << "NO\n"; }
	}
}