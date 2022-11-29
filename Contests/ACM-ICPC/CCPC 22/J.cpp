#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
        vector<int> a(n); for(auto &x : a){ cin >> x; }

        vector<int> forbidden;
        map<int, int> constraints;
        for(int i = 0; i < k; i++){
            int x, y; cin >> x >> y;
            if (y > 0){ constraints[x] = y; }
            else { forbidden.push_back(x); }
        }

        forbidden.push_back(-1);
        a.push_back(-2);

        sort(forbidden.begin(), forbidden.end());
        sort(a.begin(), a.end());

        ll available = 0;
        vector<int> curNums;
        while(!a.empty() && !forbidden.empty()){
            int curF = forbidden.back(), curA = a.back();
            if (curF > curA){
                forbidden.pop_back();

                for(auto &x : curNums){ available += x - curF - 1; }
                int curTarget = curF+1, curCnt = curNums.size();
                while(constraints.count(curTarget) && constraints[curTarget] < curCnt){
                    curCnt -= constraints[curTarget];
                    available -= curCnt;
                    curTarget++;
                }

                curNums.clear();
                continue;
            }
            curNums.push_back(curA);
            a.pop_back();
        }

        if (available % 2 == 1){
            cout << "Pico\n";
        }
        else{
            cout << "FuuFuu\n";
        }
	}
}