#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n, k, x, d; cin >> n >> k >> x >> d;

        int m; cin >> m;
        vector<vector<int>> start(d + 2), end(d + 2);
        for(int i = 0; i < m; i++){
            int p, l, r; cin >> p >> l >> r; p--;
            start[l].push_back(p);
            end[r].push_back(p);
        }

        int bestKSum = 0;
        map<int, int> employeeToNumMeetings;
        multiset<int> bestK, others;
        for(int i = 0; i < k; i++){ bestK.insert(0); }
        for(int i = k; i < n; i++){ others.insert(0); }
        others.insert(m+1);

        auto maintainSets = [&](){
            auto worstTopK = prev(bestK.end());
            auto bestOther = others.begin();

            if (*worstTopK > *bestOther){
                bestK.insert(*bestOther);
                others.insert(*worstTopK);
                bestKSum += *bestOther;

                bestKSum -= *worstTopK;
                bestK.erase(worstTopK);
                others.erase(bestOther);
            }
        };

        auto updateValue = [&](int oldV, int newV){
            auto it = bestK.find(oldV);
            if (it != bestK.end()){
                bestK.erase(it);
                bestK.insert(newV);
                bestKSum += newV - oldV;
            }
            else{
                it = others.find(oldV);
                others.erase(it);
                others.insert(newV);
            }

            maintainSets();
        };

        for(int i = 0; i < x; i++){
            for(auto &e : start[i]){
                updateValue(employeeToNumMeetings[e], employeeToNumMeetings[e] + 1);
                employeeToNumMeetings[e]++;
            }
        }

        int ans = bestKSum;
        for(int i = x; i < d; i++){
            for(auto &e : start[i]){
                updateValue(employeeToNumMeetings[e], employeeToNumMeetings[e] + 1);
                employeeToNumMeetings[e]++;
            }

            for(auto &e : end[i-x+1]){
                updateValue(employeeToNumMeetings[e], employeeToNumMeetings[e] - 1);
                employeeToNumMeetings[e]--;
            }

            ans = min(ans, bestKSum);
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}
