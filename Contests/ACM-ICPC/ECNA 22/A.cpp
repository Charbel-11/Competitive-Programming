#include <bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;
const int MX = 51*51*50*50 + 1;
int c, r, e;

struct edge {
    int v; bool w1, w2; edge() {}
    edge(int _v, bool _w1, bool _w2) : v(_v), w1(_w1), w2(_w2) {}
};

struct node { vector<edge> edges; };

struct graph {
    node nodes[MX]; int n;
    pair<int, int> dist[MX];
    graph(int _n) :n(_n) {}

    void add_edge(int u, int v, bool w1, bool w2) {
        edge e1(v, w1, w2);
        nodes[u].edges.push_back(e1);
    }

   void bfs01(int s) {
        bitset<MX> visited;
        for (int i = 0; i < MX; i++){ dist[i] = {INF, INF}; };
        vector<int> v1, v2, v3;
        //        list<int> q1, q2; q1.push_back(s);
        dist[s] = {0, 0};
        v1.push_back(s);

        while (!v1.empty() || !v2.empty() || !v3.empty()) {
            if (v1.empty()){
                if (v2.empty()){ swap(v1, v3); }
                else{
                    swap(v1, v2);
                    while(!v3.empty()){
                        v1.push_back(v3.back());
                        v3.pop_back();
                    }
                }
            }

            int cur = v1.back(); v1.pop_back();
            while (visited[cur] && !v1.empty()) { cur = v1.back(); v1.pop_back(); }
            if (visited[cur]) { continue; } visited[cur] = 1;

            for (auto &e : nodes[cur].edges) {
                if (visited[e.v]){ continue; }
                if (dist[e.v].first > dist[cur].first + e.w1 ||
                        (dist[e.v].first == dist[cur].first + e.w1 &&
                         dist[e.v].second > dist[cur].second + e.w2)){
                    dist[e.v] = dist[cur];
                    dist[e.v].first += e.w1;
                    dist[e.v].second += e.w2;

                    if (e.w1 == 0 && e.w2 == 0) { v1.push_back(e.v); }
                    else if (e.w1 == 1 && e.w2 == 0){ v2.push_back(e.v); }
                    else{ v3.push_back(e.v); }
                }
            }
        }
    }
};

int getState(int r1, int c1, int r2, int c2){
    int state = r1;
    state += c1 * r;
    state += r2 * (r * c);
    state += c2 * (r * c * r);
    return state;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> c >> r >> e; e--; r++;
    int ic1, ir1, ic2, ir2; char d1C, d2C;
    cin >> ic1 >> ir1 >> d1C >> ic2 >> ir2 >> d2C;
    ic1--; ir1--; ic2--; ir2--;
    int id1 = 0, id2 = 0;
    if (d1C == 'E'){ id1 = 1; }
    else if (d1C == 'S') { id1 = 2; }
    else if (d1C == 'W'){ id1 = 3; }
    if (d2C == 'E'){ id2 = 1; }
    else if (d2C == 'S') { id2 = 2; }
    else if (d2C == 'W'){ id2 = 3; }

    int diff = id2 - id1;

    vector<vector<set<pair<int, int>>>> lines(r, vector<set<pair<int, int>>>(c));
    int m; cin >> m;
    for(int i = 0; i < m; i++){
        int ci, ri; cin >> ci >> ri; ci--; ri--;
        lines[ri][ci].insert({ri+1, ci});
        lines[ri+1][ci].insert({ri, ci});
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        int ci, ri; cin >> ci >> ri; ci--; ri--;
        lines[ri][ci].insert({ri, ci+1});
        lines[ri][ci+1].insert({ri, ci});
    }

    int startState = getState(ir1, ic1, ir2, ic2);
    int numNodes = (c * r) * (c * r);
    graph g(numNodes);

    int dR[4] = {1, 0, -1, 0};
    int dC[4] = {0, 1, 0, -1};

    for(int r1 = 0; r1 < r; r1++){
        for(int c1 = 0; c1 < c; c1++){
            for(int r2 = 0; r2 < r; r2++){
                for(int c2 = 0; c2 < c; c2++){
                    for(int d1 = 0; d1 < 4; d1++){
                        int d2 = (d1 + diff + 4) % 4;
                        if (r1 == r-1 && r2 == r-1){ continue; }
                        if (r1 == r-1 && c1 != e){ continue; }
                        if (r2 == r-1 && c2 != e){ continue; }

                        int curState = getState(r1, c1, r2, c2);

                      /*  //Rotate R
                        int nD1 = (d1 + 1) % 4;
                        int newState = getState(r1, c1, r2, c2);
                        g.add_edge(curState, newState, 0, 0);

                        //Rotate L
                        nD1 = (d1 + 3) % 4;
                        newState = getState(r1, c1, r2, c2);
                        g.add_edge(curState, newState, 0, 0);
*/

                        //Go F
                        int bumps = 0;
                        int nR1 = r1 + dR[d1], nC1 = c1 + dC[d1];
                        int nR2 = r2 + dR[d2], nC2 = c2 + dC[d2];

                        if (r1 == r-1){ nR1 = r1; nC1 = c1; }
                        else if (r1 == 0 && c1 == e && d1 == 2){ nR1 = r-1; }
                        else if (nR1 < 0 || nC1 < 0 || nR1 >= r-1 || nC1 > c-1 ||
                        lines[r1][c1].count({nR1, nC1})){
                            nR1 = r1; nC1 = c1;
                            bumps++;
                        }

                        if (r2 == r-1){ nR2 = r2; nC2 = c2; }
                        else if (r2 == 0 && c2 == e && d2 == 2){ nR2 = r-1; }
                        else if (nR2 < 0 || nC2 < 0 || nR2 >= r-1 || nC2 > c-1 ||
                        lines[r2][c2].count({nR2, nC2})){
                            nR2 = r2; nC2 = c2;
                            bumps++;
                        }
                        if (bumps == 2){ continue; }
                        int newState = getState(nR1, nC1, nR2, nC2);

                        if (nR1 == r-1 || nR2 == r-1 || nR1 != nR2 || nC1 != nC2) {
                            g.add_edge(curState, newState, 1, bumps);
                        }
                    }
                }
            }
        }
    }

    pair<int, int> ans = {INF, INF};
     g.bfs01(startState);
    for(int d1 = 0; d1 < 4; d1++){
        int endState = getState(r-1, e, r-1, e);
        if (ans.first > g.dist[endState].first){
            ans = g.dist[endState];
        }
        else if (ans.first == g.dist[endState].first && ans.second > g.dist[endState].second){
            ans = g.dist[endState];
        }
    }
    cout << ans.first << " " << ans.second << '\n';
}