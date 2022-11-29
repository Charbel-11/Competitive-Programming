//https://atcoder.jp/contests/abc278/tasks/abc278_g

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, l, r; cin >> n >> l >> r;

    pair<int, int> goodSplit = {-1,-1};
    for(int x = 1; x <= n; x++){
        for(int y = l; y <= r; y++){
            int remL = x - 1, remR = n - (x + y - 1);
            if (remR < 0){ break; }
            if (remL == remR){
                goodSplit = {x, y};
                break;
            }
        }
    }

    if (goodSplit.first != -1){
        cout << "First" << endl;
        cout << goodSplit.first << " " << goodSplit.second << endl;

        int skipRange = goodSplit.first + goodSplit.second - 1;

        int opX, opY; cin >> opX >> opY;
        while(opX != 0 && opX != -1){
            if (opX + skipRange <= n){
                cout << opX + skipRange << " " << opY << endl;
            }
            else{
                cout << opX - skipRange << " " << opY << endl;
            }
            cin >> opX >> opY;
        }
    }
    else{
        int range = l;

        vector<int> gn(n+1, 0);
        for(int i = range; i <= n; i++){
            unordered_set<int> nextMoves;
            for(int x = 1; x + range - 1 <= i; x++){
                int curGn = gn[x-1] ^ gn[i-(x+range-1)];
                nextMoves.insert(curGn);
            }
            int curGn = 0;
            while(nextMoves.count(curGn)){ curGn++; }
            gn[i] = curGn;
        }

        map<int, int> intervals;
        intervals[1] = n;

        auto split = [&](int opX, int opY){
            auto it = prev(intervals.upper_bound(opX));
            int curL = it->first, curR = it->second;
            intervals.erase(it);

            int leftL = curL, leftR = opX - 1;
            if (leftR >= leftL){
                intervals[leftL] = leftR;
            }

            int rightL = opX + opY, rightR = curR;
            if (rightR >= rightL){
                intervals[rightL] = rightR;
            }
        };

        if (gn[n] > 0){
            cout << "First" << endl;
        }
        else{
            cout << "Second" << endl;
            int opX, opY; cin >> opX >> opY;
            if (opX == 0 || opX == -1){
                return 0;
            }
            split(opX, opY);
        }

        while(true){
            int xorSum = 0;
            for(auto &p : intervals){
                auto [curL, curR] = p;
                xorSum ^= gn[curR-curL+1];
            }

            int target = 0;
            pair<int, int> curInterval;
            for(auto &p : intervals){
                auto [curL, curR] = p;
                int curGn = gn[curR-curL+1];

                if ((xorSum ^ curGn) < curGn){
                    target = xorSum ^ curGn;
                    curInterval = {curL, curR};
                    break;
                }
            }

            auto [curL, curR] = curInterval;
            for(int x = curL; x + range - 1 <= curR; x++){
                int curGn = gn[x-curL] ^ gn[curR-(x+range-1)];
                if (curGn == target){
                    cout << x << " " << range << endl;
                    split(x, range);
                    break;
                }
            }

            int opX, opY; cin >> opX >> opY;
            if (opX == 0 || opX == -1){ return 0; }
            split(opX, opY);
        }
    }
}