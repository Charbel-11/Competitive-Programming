#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    string _; getline(cin, _);
    while(n--){
        string s; getline(cin, s);
        map<char, int> freq;
        for(auto c : s){
            if (c >= 'a' && c <= 'z') { freq[c]++; }
        }
        int mx = -1; char ans = 'a';
        for(auto &p : freq){
            if (p.first >= 'h'){ continue; }
            if (p.second > mx){
                mx = p.second;
                ans = p.first - 'a' + 'A';
            }
        }
        cout << ans << '\n';
    }
}

