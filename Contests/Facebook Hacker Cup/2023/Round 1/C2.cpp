#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n; cin >> n;
        string s; cin >> s;

        vector<int> S(n, 0);
        for(int i = 0; i < n; i++){
            S[i] = s[i] == '1';
        }

        map<int, int> m; ll ans = 0, curCnt = 0;
        for(int i = 1; i <= n; i++){
            if (S[i-1] == 1){
                curCnt++; m[i-1] = 0;
                for(int j = i; j <= n; j += i){ S[j-1]^=1; }
            }
        }

        int q; cin >> q;
        while(q--){
            int b; cin >> b; b--;
            if (m.count(b)){
                if (m[b] == 0){ curCnt--; }
                else{ curCnt++; }
                m[b] ^= 1;
            }
            else{
                curCnt++;
                m[b] = 0;
            }
            ans += curCnt;
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}