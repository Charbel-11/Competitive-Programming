#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}

    bool operator <(const edge& rhs) const{
        return v < rhs.v;
    }
};

struct node { int val; vector<edge> edges; };

struct tree {
    vector<node> nodes;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }
};

void skipSpaces(int& idx, const string& c){
    while(idx < c.size() && c[idx] == ' '){ idx++; }
}

int readNextInt(int& idx, const string& c){
    skipSpaces(idx, c);
    int num = 0;
    while(idx < c.size() && c[idx] != ' ' && c[idx] != '(' && c[idx] != ')'){
        num *= 10;
        num += c[idx] - '0';
        idx++;
    }
    skipSpaces(idx, c);
    return num;
}

void getEdges(string& c, int& idx, vector<pair<int, int>>& edges, int p = -1){
    if (idx >= c.size()){ return; }

    while(idx < c.size() && c[idx] != ')') {
        skipSpaces(idx, c);
        assert(c[idx] == '('); idx++;
        skipSpaces(idx, c);

        int curChild = readNextInt(idx, c);
        if (p != -1) { edges.emplace_back(p, curChild); }
        if (idx < c.size() && c[idx] == '(') {
            getEdges(c, idx, edges, curChild);
        }

        skipSpaces(idx, c);
        if (idx < c.size() && c[idx] == ')'){ idx++; }
        skipSpaces(idx, c);
    }
}

tree buildTree(string& c){
    int idx = 0;
    int root = readNextInt(idx, c);

    vector<pair<int, int>> edges;
    getEdges(c, idx, edges, root);

    set<int> nodesVal; nodesVal.insert(root);
    for (auto [u, v] : edges){
        nodesVal.insert(u);
        nodesVal.insert(v);
    }

    tree t(nodesVal.size());
    map<int, int> comp; int id = 0;
    for (auto u : nodesVal){
        comp[u] = id;
        t.nodes[id].val = u;
        id++;
    }
    t.root = comp[root];

    for (auto [u, v] : edges){
        t.add_edge(comp[u], comp[v]);
    }

    for(auto u : nodesVal){
        sort(t.nodes[comp[u]].edges.begin(), t.nodes[comp[u]].edges.end());
    }

    return t;
}

bool compareTrees(int node1, int node2, tree& t1, tree& t2, int p1=-1, int p2=-1){
    if (t1.nodes[node1].val != t2.nodes[node2].val){ return false;}

    auto edges1 = t1.nodes[node1].edges;
    auto edges2 = t2.nodes[node2].edges;
    if (edges1.size() != edges2.size()){ return false; }

    for(int i = 0; i < edges1.size(); i++){
        int val1 = t1.nodes[edges1[i].v].val;
        int val2 = t2.nodes[edges2[i].v].val;
        if (val1 != val2){ return false; }

        if (edges1[i].v == p1){ continue; }

        if (!compareTrees(edges1[i].v, edges2[i].v, t1, t2, node1, node2)){
            return false;
        }
    }
    return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string c1, c2;
    getline(cin, c1);
    getline(cin, c2);

    tree t1 = buildTree(c1);
    tree t2 = buildTree(c2);

    if (compareTrees(t1.root, t2.root, t1, t2, -1, -1)){ cout << "Yes\n"; }
    else { cout << "No\n"; }
}