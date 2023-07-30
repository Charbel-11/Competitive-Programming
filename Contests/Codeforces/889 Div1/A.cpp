#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> a(n); for(auto &x : a){ cin >> x; }
        bool sorted = true;
        for(int i = 1; i < n; i++){
            if (a[i-1] > a[i]){ sorted = false; break; }
        }

        if (sorted) { cout << 0 << '\n'; continue; }

        int numPos = 0, numZeros = 0, numNeg = 0;
        int maxPos = 0, maxPosIdx = -1, maxNeg = 0, maxNegIdx = -1;
        for(int i = 0; i < n; i++){
            if (a[i] > 0){
                numPos++;
                if (a[i] > maxPos){
                    maxPos = a[i];
                    maxPosIdx = i;
                }
            }
            else if (a[i] < 0){
                numNeg++;
                if (-a[i] > maxNeg){
                    maxNeg = -a[i];
                    maxNegIdx = i;
                }
            }
            else { numZeros++; }
        }

        bool allPos = true;
        vector<pair<int, int>> ans;
        if (maxPos >= maxNeg){
            if (numNeg <= 12){
                for(int i = 0; i < n; i++) {
                    if (a[i] < 0){ ans.emplace_back(i + 1, maxPosIdx + 1); }
                }
            }
            else{
                while(maxNeg < maxPos){
                    maxNeg += maxNeg;
                    ans.emplace_back(maxNegIdx+1, maxNegIdx+1);
                }
                for(int i = 0; i < n; i++){
                    if (a[i] > 0){
                        ans.emplace_back(i + 1, maxNegIdx + 1);
                    }
                }
                allPos = false;
            }
        }
        else{
            if (numPos <= 12){
                for(int i = 0; i < n; i++) {
                    if (a[i] > 0){ ans.emplace_back(i + 1, maxNegIdx + 1); }
                }
                allPos = false;
            }
            else{
                while(maxPos < maxNeg){
                    maxPos += maxPos;
                    ans.emplace_back(maxPosIdx+1, maxPosIdx+1);
                }
                for(int i = 0; i < n; i++){
                    if (a[i] < 0){
                        ans.emplace_back(i + 1, maxPosIdx + 1);
                    }
                }
            }
        }

        if (allPos){
            for(int i = 0; i < n - 1; i++){
                ans.emplace_back(i+2, i+1);
            }
        }
        else{
            for(int i = n-1; i > 0; i--) {
                ans.emplace_back(i, i + 1);
            }
        }

        cout << ans.size() << '\n';
        for(auto &p : ans){ cout << p.first << " " << p.second << '\n'; }
	}
}