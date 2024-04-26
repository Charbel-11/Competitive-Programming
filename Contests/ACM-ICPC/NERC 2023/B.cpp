#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        string s; cin >> s;

        bool OK = true, odd = false;
        reverse(s.begin(), s.end());
        while(!s.empty()){
            odd = !odd;
            if (odd){ s.pop_back(); }
            else{
                if (s.size() == 1){ OK = false; break; }
                char c = s.back(); s.pop_back();
                char c2 = s.back(); s.pop_back();
                if (c != c2) { OK = false; break; }
            }
        }

        cout << (OK? "YES": "NO") << '\n';
	}
}