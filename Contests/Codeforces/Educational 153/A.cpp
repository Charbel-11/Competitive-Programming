#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		string s; cin >> s;

        int n = s.size();
        string c1 = "", c2 = "";
        for(int i = 0; i < n; i++){
            c1.push_back('(');
            c2.push_back('(');
            c2.push_back(')');
        }
        for(int i = 0; i < n; i++){
            c1.push_back(')');
        }

        bool in1 = false, in2 = false;
        for(int i = 0; i <= n; i++){
            bool curIn1 = true, curIn2 = true;
            for(int j = 0; j < n; j++){
                if (c1[i+j] != s[j]){ curIn1 = false; break; }
            }
            for(int j = 0; j < n; j++){
                if (c2[i+j] != s[j]){ curIn2 = false; break; }
            }
            in1 = in1 || curIn1;
            in2 = in2 || curIn2;
        }

        if (in1 && in2) { cout << "NO\n"; }
        else{
            cout << "YES\n";
            if(!in1){cout << c1 << '\n';}
            else{cout << c2 << '\n';}
        }
	}
}