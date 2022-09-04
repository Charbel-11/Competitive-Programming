#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        string s; cin >> s;

        string ans = "";
        if (s[0] != '9') {
            for(int i = 0; i < n; i++){
                ans.push_back('9' - (s[i]-'0'));
            }
        }
        else{
            int carry = 0;
            for(int i = n-1; i>= 0; i--){
                int cur = carry + s[i] - '0';
                if (cur == 0){ ans.push_back('1'); carry = 0; }
                else if (cur == 1) { ans.push_back('0'); carry = 0; }
                else{ ans.push_back('0'+ 11 - cur); carry = 1; }
            }

            reverse(ans.begin(), ans.end());
        }

        cout << ans << '\n';
    }
}
