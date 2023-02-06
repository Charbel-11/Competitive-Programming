#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
    sort(s.begin(), s.end());

    int n = s.size();
    if (n == 1){ cout << s << '\n'; return 0; }

    int j = 1;
    for (int i = 1; i < n; i++){
        if (s[i] != s[i-1]){ continue; }
        if (s[i] == s.back()){ break; }

        j = max(j, i + 1);
        while(s[j] == s[i]){ j++; }
        swap(s[i], s[j]);
    }

    bool OK = true;
    if (s[n-2] == s[n-1]) {
        string rem;
        int last = n - 1;
        while (last > 0 && s[last] == s[last - 1]){
            rem.push_back(s[last]);
            s.pop_back();
            last--;
        }

        string ansRev;
        reverse(s.begin(), s.end());
        for(int i = 0; i < s.size(); i++){
            if (rem.empty() || s[i] == rem.back() || ansRev.back() == rem.back()){
                ansRev.push_back(s[i]);
                continue;
            }
            ansRev.push_back(rem.back());
            rem.pop_back();
            i--;
        }

        if (!rem.empty() && ansRev.back() != rem.back()){
            ansRev.push_back(rem.back());
            rem.pop_back();
        }

        if (!rem.empty()){ OK = false; }
        else{
            s = ansRev;
            reverse(s.begin(), s.end());

            string part1;
            int i = 0;
            for(; s[i] != s.back(); i++){
                part1.push_back(s[i]);
            }

            string sep, alt;
            bool addToSep = true;
            for(; i < s.size(); i++){
                if (addToSep){ sep.push_back(s[i]); }
                else{ alt.push_back(s[i]); }
                addToSep = !addToSep;
            }

            sort(alt.begin(), alt.end());
            for(i = 0; i < alt.size(); i++){
                part1.push_back(sep.back());
                part1.push_back(alt[i]);
            }
            part1.push_back(sep.back());
            s = part1;
        }
    }

    if (!OK){ cout << -1 << '\n'; }
    else{ cout << s << '\n'; }
}