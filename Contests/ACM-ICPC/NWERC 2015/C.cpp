#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
    ll x, y; Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

    bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
    Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
    Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }

    friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll dotProduct(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

//0: Colinear; 1: Clockwise (C is to the right of (AB)); 2: Counterclockwise (C is to the left of (AB))
int orientation(const Point& A, const Point& B, const Point& C) {
    ll x = crossProduct(C - B, B - A);
    return x ? 1 + (x < 0) : 0;
}

// Checks whether P is in the segment [AB]
bool pointInsideSegment(const Point& A, const Point& B, const Point& P) {
    if (P == A || P == B) { return true; }
    return crossProduct(A - P, B - P) == 0 && dotProduct(A - P, B - P) < 0;
}

// Checks whether segments [A1 B1] and [A2 B2] intersect
bool intersectionSegmentSegment(const Point& A1, const Point& B1, const Point& A2, const Point& B2) {
    int O1 = orientation(A1, B1, A2), O2 = orientation(A1, B1, B2);
    int O3 = orientation(A2, B2, A1), O4 = orientation(A2, B2, B1);
    if (O1 != O2 && O3 != O4) { return true; }

    if (O1 || O2) { return false; }
    if (pointInsideSegment(A1, B1, A2)) { return true; }
    if (pointInsideSegment(A1, B1, B2)) { return true; }
    if (pointInsideSegment(A2, B2, A1)) { return true; }
    return false;
}


struct Edge {
    int u, v; int w; Edge() {}
    Edge(int _u, int _v, int _w = 1) :
            u(_u), v(_v), w(_w) {}
};

struct Node { vector<Edge> edges; };

struct Graph {
    vector<Node> nodes; int n;
    bool bipartite = true;
    vector<int> color;

    Graph(int _n) : n(_n) { nodes.resize(n); color.resize(n, -1); }

    void addEdge(int u, int v) {
        Edge e1(u, v); nodes[u].edges.push_back(e1);
        Edge e2(v, u); nodes[v].edges.push_back(e2);
    }

    void dfs(int u){
        if (color[u] == -1){ color[u] = 0; }
        int otherColor = 1-color[u];
        for(auto &e : nodes[u].edges){
            if (color[e.v] == -1){
                color[e.v] = otherColor;
                dfs(e.v);
            }
            else if (color[e.v] != otherColor){
                bipartite = false; break;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int w, p; cin >> w >> p;

    vector<Point> wells;
    for(int i = 0; i < w; i++){
        ll x, y; cin >> x >> y;
        wells.emplace_back(x, y);
    }

    vector<pair<Point, Point>> pipes;
    for(int i = 0; i < p; i++){
        int s; cin >> s; s--;
        ll x, y; cin >> x >> y;
        Point start(wells[s]), end(x, y);
        pipes.push_back({start, end});
    }

    Graph g(p);
    for(int i = 0; i < p; i++){
        for(int j = i+1; j < p; j++){
            if (pipes[i].first == pipes[j].first){ continue; }
            if (intersectionSegmentSegment(pipes[i].first, pipes[i].second, pipes[j].first, pipes[j].second)){
                g.addEdge(i, j);
            }
        }
    }

    for(int i = 0; i < p; i++){
        if (g.color[i] == -1){ g.dfs(i); }
    }
    if (g.bipartite){ cout << "possible\n"; }
    else{ cout << "impossible\n"; }
}