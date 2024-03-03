#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
    ll x, y; Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
    Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
    Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }
    bool operator < (const Point& rhs) const {
        return (x != rhs.x) ? x < rhs.x : y < rhs.y;
    }
};

ll crossProduct(Point A, Point B) { return A.x * B.y - A.y * B.x; }

ll area(std::span<Point> polygon) { //Returns double the area
    ll a = 0; int n = (int)polygon.size() - 1;
    for (int i = 0; i < n; i++)
        a += crossProduct(polygon[i], polygon[i + 1]);
    return abs(a);
}

//0: Colinear 1: Clockwise 2: Counterclockwise
int orientation(Point& A, Point& B, Point& C) {
    ll x = crossProduct(C - B, B - A);
    return x ? 1 + (x < 0) : 0;
}

//Returns Hull Sorted Counter-Clockwise
vector<Point> convexHullGrahamScan(vector<Point> P) {
    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());
    int n = (int)P.size(); if (n < 3) { return P; }

    vector<Point> res;
    auto incorrect = [&](Point& A, Point& B, Point& C) {
        //Change to == 1 to keep points on CH boundary
        //Chnage to (!= 1 / == 2) to sort Clockwise
        return orientation(A, B, C) != 2;
    };

    int m = 0; for (int i = 0; i < n; ++i) {
        while (m > 1 && incorrect(res[m - 2], res[m - 1], P[i])) { res.pop_back(); --m; }
        res.push_back(P[i]); ++m;
    }

    for (int i = n - 2, M = m; i >= 0; i--) {
        if (P[i] == res[m - 2]) { continue; }
        while (m > M && incorrect(res[m - 2], res[m - 1], P[i])) { res.pop_back(); --m; }
        res.push_back(P[i]); ++m;
    }

    return res;
}

ll DP[1000000][2];
vector<Point> points;
vector<pair<int, int>> diagonals;
vector<int> areas;

struct DSU {
    vector<int> parent_diagonal;
    vector<set<int>> children_edge;
    vector<set<int>> children_diagonal;
    int NUM_LIST = 1;

    DSU(int n, const vector<pair<int, int>> &diagonals)
            : parent_diagonal(diagonals.size()), children_edge(1), children_diagonal(1) {
        fill(parent_diagonal.begin(), parent_diagonal.end(), 0);
        for (int i = 0; i < n; i++) children_diagonal[0].insert(i);
        for(int i = 0; i < points.size(); ++i) children_edge[0].insert(i);
    }

    void split(int diagonal_idx) {
        auto&[L, R] = diagonals[diagonal_idx];
        int u = parent_diagonal[diagonal_idx];
        int even = 0, odd = 0;
        auto parity = [&](pair<int, int> P) { return P.first >= L && P.second <= R; };

        for(auto &edge : children_edge[u]) ++(parity({edge, edge + 1}) ? odd : even);
        for(auto &diagonal : children_diagonal[u])
            if(diagonal != diagonal_idx) ++(parity(diagonals[diagonal]) ? odd : even);

        bool required_parity = odd < even;
        children_edge.emplace_back(); auto &new_edge = children_edge.back();
        children_diagonal.emplace_back(); auto &new_diagonal = children_diagonal.back();

        for(auto &edge : children_edge[u])
            if(parity({edge, edge + 1}) == required_parity)
                new_edge.insert(edge);
        for(auto &diagonal : children_diagonal[u])
            if(diagonal != diagonal_idx && parity(diagonals[diagonal]) == required_parity)
                new_diagonal.insert(diagonal);

        for(auto &edge : new_edge) children_edge[u].erase(edge);
        for(auto &diagonal : new_diagonal) {
            parent_diagonal[diagonal] = NUM_LIST;
            children_diagonal[u].erase(diagonal);
        }
        new_diagonal.insert(diagonal_idx);
        ++NUM_LIST;
    }
};

struct Tree {
    vector<vector<int>> nodes; int n;
    Tree(int _n) : n(_n), nodes(_n) {}

    void add_edge(int u, int v) {
        nodes[u].push_back(v);
        nodes[v].push_back(u);
    }

    int MaxIndependentSet(int cur, bool take, int p = -1) {
        if (DP[cur][take] != -1) { return DP[cur][take]; }

        ll ans = take * areas[cur];
        for (int &e : nodes[cur]) if (e != p) {
                int exclude_child = MaxIndependentSet(e, 0, cur);
                int include_child = MaxIndependentSet(e, 1, cur);
                ans += take ? exclude_child : max(exclude_child, include_child);
            }
        return DP[cur][take] = ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    size_t n, m; cin >> n >> m;
    points.resize(n); diagonals.resize(m); areas.resize(m);
    for(auto &[x, y] : points) cin >> x >> y;
    for(auto &[a, b] : diagonals)  { cin >> a >> b; if (--a > --b) swap(a, b); }

    DSU dsu(m, diagonals);
    for(int i = 0; i < m; i++) { dsu.split(i); }
    vector<vector<int>> tree_edges(m);
    for(int i = 0; i <= m; ++i)
        for(auto &e : dsu.children_diagonal[i])
            tree_edges[e].push_back(i);

    Tree T(m + 1);
    for(auto &edge : tree_edges){
        assert(edge.size() == 2);
        T.add_edge(edge[0], edge[1]);
    }

    for(int i = 0; i <= m; ++i){
        vector<Point> polygon;
        for(auto &edge : dsu.children_edge[i]) {
            polygon.push_back(points[edge]);
            polygon.push_back(points[(edge + 1) % n]);
        }
        for(auto &idx : dsu.children_diagonal[i]) {
            polygon.push_back(points[diagonals[idx].first]);
            polygon.push_back(points[diagonals[idx].second]);
        }
        polygon = convexHullGrahamScan(polygon);
        areas[i] = area(polygon);
    }

    memset(DP, -1, sizeof DP);
    cout << max(T.MaxIndependentSet(0, 0), T.MaxIndependentSet(0, 1)) << '\n';
}