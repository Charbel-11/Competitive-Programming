#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, m; cin >> n >> m;
        vector<pair<int, int>> ops(m);
        for(auto &p : ops){ cin >> p.first >> p.second; }
        ops.emplace_back(0, 0);
        sort(ops.begin(), ops.end());

        bool OK = true;
        for(int i = 1; i < ops.size(); i++){
            if (ops[i].first == ops[i-1].first && ops[i].second != ops[i-1].second){
                OK = false; break;
            }
            else if (ops[i].first == ops[i-1].first){
                continue;
            }

            int timeDiff = ops[i].first - ops[i-1].first;
            if (ops[i].second > ops[i-1].second){
                int valDiff = ops[i].second - ops[i-1].second;
                if (valDiff == timeDiff){ continue; }
                if (ops[i].second < timeDiff){ continue; }
                OK = false;
                break;
            }
            else if (ops[i].second >= timeDiff){
                OK = false;
                break;
            }
        }

        if (OK){ cout << "Yes\n"; }
        else { cout << "No\n"; }
	}
}

