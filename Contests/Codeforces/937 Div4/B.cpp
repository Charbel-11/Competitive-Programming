#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<string> ans(2*n, string(2*n, '.'));

        for(int i = 0; i < 2 * n; i+=2){
            for(int j = 0; j < 2 * n; j += 2){
                if ((i + j) % 4 == 0)
                    ans[i][j] = ans[i+1][j] = ans[i][j+1] = ans[i+1][j+1] = '#';
            }
        }

        for(auto &s : ans){ cout << s << '\n'; }
	}
}

