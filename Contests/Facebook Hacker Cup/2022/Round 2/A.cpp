#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool areEqual(vector<int>& v1, vector<int>& v2){
    if (v1.size() != v2.size()){ return false; }
    for(int i = 0; i < v1.size(); i++){
        if (v1[i] != v2[i]){ return false; }
    }
    return true;
}

bool almostEqual(vector<int>& v1, vector<int>& v2){
    if (v1.size() != v2.size()){ return false; }
    bool oneMore = false;

    for(int i = 0; i < v1.size(); i++){
        if (v1[i] == v2[i]){ continue; }
        else if (v1[i] == v2[i] + 1){
            if (!oneMore){ oneMore = true; }
            else { return false; }
        }
        else{ return false; }
    }

    return oneMore;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        string s; cin >> s; int n = s.size();
        int q; cin >> q;

        vector<vector<int>> freq(n, vector<int>(26, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; i > 0 && j < 26; j++){
                freq[i][j] += freq[i-1][j];
            }
            freq[i][s[i]-'a']++;
        }

        int ans = 0;
        while(q--){
            int l, r; cin >> l >> r; l--; r--;
            if ((r-l+1) % 2 == 0){ continue; }
            if (l == r){ ans++; continue; }
            int mid = (l+r)/2;

            vector<int> freq1 = freq[mid-1];
            vector<int> freq2 = freq[r];
            for(int j = 0; j < 26; j++){
                freq1[j] -= (l > 0 ? freq[l-1][j] : 0);
                freq2[j] -= freq[mid][j];
            }

            if (areEqual(freq1, freq2)){ ans++; continue; }
            freq1[s[mid]-'a']++;
            if (almostEqual(freq1, freq2)){ ans++; continue; }
            freq1[s[mid]-'a']--;
            freq2[s[mid]-'a']++;
            if (almostEqual(freq2, freq1)){ ans++; continue; }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}