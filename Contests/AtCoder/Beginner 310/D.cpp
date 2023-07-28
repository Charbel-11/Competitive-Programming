#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int countTeams(const vector<vector<bool>>& dont, vector<vector<int>>& teams, int left, int t){
    if (left == 0 && teams.size() == t){ return 1; }
    if (left == 0){ return 0; }
    if (teams.size() > t){ return 0; }
    if (teams.size() + left < t){ return 0; }

    int curIdx = left-1, ans = 0;
    for(int i = 0; i < teams.size(); i++){
        bool OK = true;
        for(auto &x : teams[i]){
            if (dont[x][curIdx]) { OK=false; break; }
        }
        if (OK){
            teams[i].push_back(curIdx);
            ans += countTeams(dont, teams, left-1, t);
            teams[i].pop_back();
        }
    }
    teams.push_back({curIdx});
    ans += countTeams(dont, teams, left-1, t);
    teams.pop_back();

    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, t, m; cin >> n >> t >> m;
    vector<vector<bool>> dont(n, vector<bool>(n, 0));
    for(int i = 0; i < m; i++){
        int u,v; cin >> u >> v; u--; v--;
        dont[u][v] = dont[v][u] = true;
    }

    vector<vector<int>> a;
    cout << countTeams(dont, a, n, t) << '\n';
}