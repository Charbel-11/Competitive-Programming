#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> getDivisors(int n){
    vector<int> ans;
    for(int d = 1; d * d <= n; d++){
        if (n % d == 0) {
            ans.push_back(d);
            if (d * d != n){ ans.push_back(n/d); }
        }
    }
    return ans;
}

bool test(string& s, string& t){
    int numDiff = 0, n = s.size(), m = t.size();
    for(int i = 0; i < n; i += m){
        for(int j = i; j < i + m; j++){
            if (s[j] != t[j-i]){
                numDiff++;
            }
        }
        if (numDiff > 1){ return false; }
    }
    return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
	    int n; cin >> n;
        string s; cin >> s;

        int ans = n;
        auto div = getDivisors(n);
        for(auto d : div){
            if (d == n){ continue; }
            string s1 = s.substr(0, d);
            string s2 = s.substr(n-d, d);

            if (test(s, s1) || test(s, s2)){
                ans = min(ans, d);
            }
        }

        cout << ans << '\n';
	}
}

