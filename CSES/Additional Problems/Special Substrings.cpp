#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s; cin >> s;

    set<char> seen;
    for(char c: s){ seen.insert(c); }

    int missing = seen.size();
    map<vector<int>, int> dp;
    vector<int> freq(26, 0);
    dp[freq]++; ll ans = 0;

    for(char c : s) {
        freq[c-'a']++;
        if (freq[c-'a'] == 1){ missing--; }

        if (!missing){
            for (auto& x : freq) {
                if (x == 0){ continue; }
                if (--x == 0){ missing++; }
            }
        }

        ans += dp[freq];
        dp[freq]++;
    }

    cout << ans << '\n';
}