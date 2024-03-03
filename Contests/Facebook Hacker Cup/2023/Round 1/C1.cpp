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

        map<int, int> m;
        int q; cin >> q;
        while(q--){
            int b; cin >> b;
            m[b]++;
        }

        vector<int> buttons;
        for(auto &p : m){
            if (p.second % 2 == 1){ buttons.push_back(p.first); }
        }
        sort(buttons.begin(), buttons.end());

        for(int b : buttons){
            for(int i = b; i <= n; i += b){
                S[i - 1] ^= 1;
            }
        }

        int ans = 0;
        for(int i = 1; i <= n; i++){
            if (S[i-1] == 1){
                ans++;
                for(int j = i; j <= n; j += i){ S[j-1]^=1; }
            }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}