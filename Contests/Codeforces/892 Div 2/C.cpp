#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin>> n;

        int ans = 0;
        for(int j = 1; j <= n; j++){
            for(int pj = 1; pj <= n; pj++){
                int curAns = 0, maxJ = j*pj;

                set<int> left;
                for(int i = 1; i <= n; i++){
                    if (i == pj){ continue;}
                    left.insert(i);
                }

                bool OK = true;
                for(int i = n; i >= 1; i--){
                    if (i == j){ continue; }
                    int upBnd = maxJ / i;
                    auto it = left.upper_bound(upBnd);
                    if (it == left.begin()){ OK = false; break; }
                    it = prev(it);
                    curAns += i * (*it);
                    left.erase(it);
                }

                if (OK){ ans = max(ans, curAns); }
            }
        }

        cout << ans << '\n';
	}
}
