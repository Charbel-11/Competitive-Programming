#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <set>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { 
	int median, val = 0; 
	vector<edge> edges; 
};

multiset<int> med1, med2;

void balanceSets() {
	while (med1.size() > med2.size() + 1) {
		int max1 = *med1.rbegin();
		med1.erase(med1.find(max1));
		med2.insert(max1);
	}
	while (med2.size() > med1.size()) {
		int min2 = *med2.begin();
		med2.erase(med2.find(min2));
		med1.insert(min2);
	}
}

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	//turn 0 to maximize
	void dfs(int u, int p, bool turn) {
		if (med1.empty() || nodes[u].val < *med1.rbegin()) { med1.insert(nodes[u].val); }
		else { med2.insert(nodes[u].val); }
		balanceSets();

		int minMed = INT_MAX, maxMed = INT_MIN;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u, !turn);

			minMed = min(minMed, nodes[e.v].median);
			maxMed = max(maxMed, nodes[e.v].median);
		}

		if (nodes[u].edges.size() == 1 && u != 0) {
			if (med1.size() == med2.size()) {
				minMed = maxMed = *med1.rbegin() + *med2.begin();
			}
			else{
				minMed = maxMed = *med1.rbegin() * 2;
			}
		}

		if (turn == 0) { nodes[u].median = maxMed; }
		else { nodes[u].median = minMed; }

		if (med2.count(nodes[u].val)) {
			med2.erase(med2.find(nodes[u].val));
		}
		else if (med1.count(nodes[u].val)) {
			med1.erase(med1.find(nodes[u].val));
		}
		balanceSets();
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n; i++) { cin >> t.nodes[i].val; }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	t.dfs(0, -1, 0);

	cout << t.nodes[0].median / 2;
	if (t.nodes[0].median % 2) { cout << ".5"; }
	cout << '\n';
}