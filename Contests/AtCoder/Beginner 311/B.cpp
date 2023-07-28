#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N, D; cin >> N >> D;
    vector<bitset<100>> v;
    for(int i = 0; i < N; i++){
        string s; cin >> s;
        bitset<100> cur;
        for(int j = 0; j < s.size(); j++){
            if (s[j] == 'o') { cur[j] = 1; }
        }
        v.push_back(cur);
    }

    bitset<100> all = v[0];
    for(int i = 1; i < N; i++){
        all = all & v[i];
    }
    int ans = 0, cur = 0;
    for(int j = 0; j < D; j++){
        if (all[j] == 0){ ans = max(ans, cur); cur = 0; }
        else{ cur++; }
    }
    ans = max(ans, cur);

    cout << ans << '\n';
}