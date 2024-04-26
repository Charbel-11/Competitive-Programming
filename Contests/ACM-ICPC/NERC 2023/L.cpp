#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	unordered_map<string, int> dayToIdx = {
            {"Monday",0}, {"Tuesday", 1}, {"Wednesday", 2}, {"Thursday", 3},
            {"Friday", 4}, {"Saturday", 5}, {"Sunday", 6}
    };

    int n, m, k; cin >> n >> m >> k;
    vector<vector<bool>> worksOn(n, vector<bool>(7, false));
    for(int i = 0; i < n; i++){
        int t; cin >> t;
        while(t--){
            string s; cin >> s;
            worksOn[i][dayToIdx[s]] = true;
        }
    }

    unordered_set<int> holidays;
    for(int i = 0; i < m; i++){
        int h; cin >> h; h--;
        holidays.insert(h);
    }

    vector<vector<int>> projects(k);
    for(int i = 0; i < k; i++){
        int t; cin >> t;
        projects[i].resize(t);
        for(auto &x : projects[i]){ cin >> x; x--; }
        reverse(projects[i].begin(), projects[i].end());
    }

    vector<set<int>> currentProjects(n);
    auto updateProject = [&](int p, vector<set<int>>& curWorkDays){
        int cur = projects[p].back();
        projects[p].pop_back();
        if (currentProjects[cur].empty()){
            for(int d = 0; d < 7; d++){
                if (worksOn[cur][d]){
                    curWorkDays[d].insert(cur);
                }
            }
        }
        currentProjects[cur].insert(p);
    };

    int done = 0; vector<int> ans(k);
    vector<set<int>> workingOn(7, set<int>());
    for(int i = 0; i < k; i++){
        updateProject(i, workingOn);
    }
    for(int idx = 0; done < k; idx++){
        if (holidays.count(idx)){ continue; }
        int d = idx % 7;

        vector<int> changedProjects; set<int> noWorkFor;
        for(auto x : workingOn[d]){
            int p1 = *currentProjects[x].begin();
            currentProjects[x].erase(currentProjects[x].begin());

            if (currentProjects[x].empty()){ noWorkFor.insert(x); }
            if (projects[p1].empty()){ ans[p1] = idx+1; done++; }
            else{ changedProjects.push_back(p1); }
        }

        for(auto p : changedProjects){
            updateProject(p, workingOn);
        }
        for(auto x : noWorkFor){
            if (currentProjects[x].empty()){
                for(int dd = 0; dd < 7; dd++){
                    if (worksOn[x][dd]){
                        workingOn[dd].erase(x);
                    }
                }
            }
        }
    }

    for(auto &x : ans){ cout << x << ' '; }
}
