#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		string s; cin >> s;

        bool OK = true; vector<int> sorted;
        for(auto &c : s){
            if (c == '+'){
                if (sorted.empty()){ sorted.push_back(1); }
                else{
                    if (sorted.back() == 0){ sorted.push_back(0); }
                    else{ sorted.push_back(-1); }
                }
            }
            else if (c == '-'){
                if (sorted.back() == 1){
                    sorted.pop_back();
                    if (!sorted.empty()){ sorted.back() = 1; }
                }
                else{ sorted.pop_back(); }
            }
            else if (c == '1'){
                if (!sorted.empty() && sorted.back() == 0){ OK = false; break; }
                if (!sorted.empty()) { sorted.back() = 1; }
            }
            else{
                if (sorted.empty() || sorted.back() == 1){ OK = false; break; }
                sorted.back() = 0;
            }
        }

        if (OK){ cout << "YES\n"; }
        else{ cout << "NO\n"; }
	}
}