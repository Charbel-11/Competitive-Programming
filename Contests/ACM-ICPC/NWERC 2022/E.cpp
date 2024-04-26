#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    bool OK = false;
    string s; cin >> s;
    string aS, bS; int sidx = 0;
    for(; sidx < s.size(); sidx++){
        if (s[sidx] == '/') { break; }
        aS.push_back(s[sidx]);
    }
    sidx++;
    for(; sidx < s.size(); sidx++){
        bS.push_back(s[sidx]);
    }
    int a = stoi(aS), b = stoi(bS);

    for(int n = 2; n <= 1000000; n++){
        if (n * a % b != 0){ continue; }
        int sum = n * a / b;
        int low = n-1, high = n*(n-1)/2;
        if (sum < low || sum > high){ continue; }

        int prevMaxVal = 0;
        for(int maxVal = 1; maxVal <= n-1; maxVal++){
            int curMaxVal = maxVal * (maxVal-1)/2; //0, 1, ..., maxVal - 1
            curMaxVal += maxVal * (n - maxVal);
            if (curMaxVal < sum){ prevMaxVal = curMaxVal; continue; }

            int numMaxVal = sum - prevMaxVal, cnt = 0;
            cout << n << ' ' << n-1 << '\n';
            for(int i = 1; i <= maxVal; i++){
                cnt++; cout << i << ' ' << i + 1 << '\n';
            }
            int idx = maxVal + 2;
            for(int i = 0; i < numMaxVal - 1; i++){
                cnt++; cout << maxVal << ' ' << idx++ << '\n';
            }
            while(cnt < n - 1){
                cnt++; cout << maxVal - 1 << ' ' << idx++ << '\n';
            }

            OK = true; break;
        }
        if (OK){ break; }
    }

    if (!OK) { cout << "impossible\n"; }
}