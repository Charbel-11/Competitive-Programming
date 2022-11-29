#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    set<string> winners;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 5; j++){
            string cur; cin >> cur;
            winners.insert(cur);
        }
    }

    int numWinners[5], numNonWinners[5];
    for(int j = 0; j < 5; j++){
        numWinners[j] = numNonWinners[j] = 0;
    }

    int m; cin >> m;
    for(int i = 0; i < m; i++){
        string curN; cin >> curN;
        int curPos; cin >> curPos; curPos--;
        if (winners.count(curN)){
            numWinners[curPos]++;
        }
        else{
            numNonWinners[curPos]++;
        }
    }

    auto countBits = [](int num) {
        int ans = 0;
        while(num){
            ans++; num &= (num-1);
        }
        return ans;
    };

    int ans = 0;
    for (int i = 1; i <= 5; i++) {
        for (m = 0; m < (1 << 5); m++) {
            if (countBits(m) != i) { continue; }

            int minCur = 1e5;
            for(int j = 0; j < 5; j++){
                if (m & (1<<j)){
                    minCur = min(minCur, numWinners[j]);
                }
                else{
                    minCur = min(minCur, numNonWinners[j]);
                }
            }

            ans += minCur;

            for(int j = 0; j < 5; j++){
                if (m & (1<<j)){
                    numWinners[j] -= minCur;
                }
                else{
                    numNonWinners[j] -= minCur;
                }
            }
        }
    }

    cout << ans << '\n';
}