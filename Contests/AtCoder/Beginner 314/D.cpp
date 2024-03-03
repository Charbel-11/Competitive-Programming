#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    string s; cin >> s;
    int q; cin >> q;

    int changeAfter = -1;
    bool allCap = true;
    vector<pair<int, char>> changes;
    changes.emplace_back(0, s[0]);
    while(q--){
        int t, x; char c; cin >> t >> x >> c; x--;
        if (t==1) { changes.emplace_back(x, c); }
        else{
            changeAfter = changes.size() - 1;
            if (t == 2){ allCap = false; }
            else { allCap = true; }
        }
    }

    for(int i = 0; i < changes.size(); i++){
        auto p = changes[i];
        s[p.first] = p.second;
        if (changeAfter == i){
            if (allCap){
                for(auto &c : s){
                    if (c >= 'A' && c <= 'Z') { continue; }
                    else{ c = c - 'a' + 'A'; }
                }
            }
            else{
                for(auto &c : s){
                    if (c >= 'a' && c <= 'z') { continue; }
                    else{ c = c - 'A' + 'a'; }
                }
            }
        }
    }

    cout << s << '\n';
}