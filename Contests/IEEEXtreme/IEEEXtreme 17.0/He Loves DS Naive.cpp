#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int SVSZ = 300009;
typedef int(*func_ptr) (int&, int&, int&);

int spf[SVSZ]; //Smallest Prime Factor
int hpp[SVSZ]; //Highest Power of spf
int hpc[SVSZ]; //Highest Power Count of spf
int func[SVSZ];//Multiplicative Function
vector<int> primes; int ONE = 1;
vector<int> ans;

int identity(int &HPP, int &HPC, int &SPF) { return HPP; }
int divCount(int &HPP, int &HPC, int &SPF) { return HPC + 1; }
int divSum(int &HPP, int &HPC, int &SPF) { return (HPP * SPF - 1) / (SPF - 1); }
int eulerTot(int &HPP, int &HPC, int &SPF) { return HPP - HPP / SPF; }
int mobius(int &HPP, int &HPC, int &SPF) { return (HPC == 0) - (HPC == 1); }

int f(int HPP, int HPC, int SPF) { return 0; } //Modify accordingly

void buildSieveMult(func_ptr Mult) { //Computes a multiplicative function over a range in O(n)
    spf[0] = spf[1] = hpp[1] = func[1] = 1; //Initial Values
    hpp[0] = hpc[0] = hpc[1] = func[0] = 0; //Initial Values

    for (int i = 2; i < SVSZ; i++) {
        if (spf[i] == 0) { //i is Prime
            primes.push_back(i); spf[i] = i;
            func[i] = Mult(i, ONE, i); hpp[i] = i; hpc[i] = 1;
        }
        for (int j = 0; j < (int)primes.size() && i * primes[j] < SVSZ; j++) {
            spf[i * primes[j]] = primes[j];
            if (i % primes[j]) { //primes[j] < spf[i]
                func[i * primes[j]] = func[i] * func[primes[j]];
                hpp[i * primes[j]] = primes[j]; hpc[i*primes[j]] = 1;
            }
            else { //primes[j] == spf[i]
                hpp[i * primes[j]] = primes[j] * hpp[i]; hpc[i * primes[j]] = 1 + hpc[i];
                func[i * primes[j]] = func[i / hpp[i]] * Mult(hpp[i * primes[j]], hpc[i * primes[j]], primes[j]);
                break;
            }
        }
    }
}

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node {
    vector<edge> edges;
};

struct tree {
    vector<int> start, finish, order, depth, orderDepth;
    vector<int> prepAns; vector<node> nodes;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        nodes.resize(n); depth.resize(n);
        prepAns.resize(n, 0);
    }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    void getDepth(int u, int p, int d){
        depth[u] = d;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            getDepth(e.v, u, d+1);
        }
    }

    void dfs(int u, int curD, int remD, int l){
        if (remD < 0){ return; }
        ans[u] = func[l + curD];
        for(auto &e : nodes[u].edges){
            if (depth[e.v] < depth[e.u]){ continue; } //parent
            dfs(e.v, curD+1, remD-1, l);
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    buildSieveMult(eulerTot);

    int n; cin >> n; tree t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
    }

    t.getDepth(0, -1, 0);

    ans.clear(); ans.resize(n, 0);
    int q; cin >> q;
    for(int T = 0; T < q; T++){
        int type; cin >> type;
        if (type == 1){
            int v, l, r; cin >> v >> l >> r; v--;
            t.dfs(v, 0, r-l, l);
        }
        else{
            int u; cin >> u; u--;
            cout << ans[u] << '\n';
        }
    }
}