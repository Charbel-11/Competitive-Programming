#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    unordered_map<string, vector<int>> m;
    for(int i = 0; i < n; i++){
        string name, type; cin >> name >> type;
        int cnt; cin >> cnt;
        if (!m.count(name)){ m[name] = {0, 0, 0}; }
        if (type == "left"){ m[name][0] += cnt; }
        else if (type == "right"){ m[name][1] += cnt; }
        else{ m[name][2] += cnt; }
    }

    int ans = 0; bool OK = false;
    for(auto &p : m){
        auto v = p.second;
        if (v[0] == 0 && v[1] == 0){ ans++; }
        else{ ans += max(v[0], v[1]); }
        if (v[2] > 1 || (v[0] > 0 && v[1] > 0) || (v[2] > 0 && (v[0] > 0 || v[1] > 0))){
            OK = true;
        }
    }

    if (!OK){ cout << "impossible\n"; }
    else{ cout << ans + 1 << '\n'; }
}