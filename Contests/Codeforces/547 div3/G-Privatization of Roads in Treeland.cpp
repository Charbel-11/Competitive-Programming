#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>

using namespace std;

struct edge_t {
	int dest;

	edge_t() {}
	edge_t(int ad) : dest(ad) {}
};

struct node_t {
	int name;
	vector<edge_t> edges;
	int inDegree;


	node_t() {}
	node_t(int an) : name(an), inDegree(0) {}
};

struct graph_t {
	map<int, node_t> nodes;

	void populateDegrees(int node = 1) {
		set<int> visited;
		stack<int> S;

		S.push(node);
		visited.insert(node);

		while (!S.empty()) {
			int t = S.top();
			S.pop();

			node_t curN = nodes[t];

			for (edge_t e : curN.edges) {
				nodes[e.dest].inDegree++;

				if (visited.count(e.dest) == 0) {
					S.push(e.dest);
					visited.insert(e.dest);
				}
			}
		}
	}
};


int main() {
	int n, k;
	cin >> n >> k;

	graph_t graph;
	for (int i = 0; i < n; i++) {			//create nodes
		graph.nodes[i + 1] = node_t(i + 1);
	}

	map<pair<int, int>, int> preA;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;

		preA[{u, v}] = i;
		preA[{v, u}] = i;
		graph.nodes[u].edges.push_back(edge_t(v));
		graph.nodes[v].edges.push_back(edge_t(u));	//if undirected
	}

	graph.populateDegrees();

	multimap<int, int> degrees;

	map<int, node_t>::iterator itr = graph.nodes.begin();
	while (itr != graph.nodes.end()) {
		int temp = itr->second.inDegree;
		degrees.insert({ temp, itr->first });

		itr++;
	}

	int r = 1;
	multimap<int, int>::iterator itr2 = prev(degrees.end());
	while (k > 0 && itr2 != prev(degrees.begin())) {
		itr2--;
		k--;
	}
	if (itr2 != prev(degrees.begin())) {
		r = itr2->first;
	}
	else {
		cout << 1 << endl;
		for (int i = 0; i < n - 1; i++) {
			cout << 1 << " ";
		}
		cout << endl;
		return 0;
	}

	cout << r << endl;

	//in-degree = out-degree since undirected
	vector<int> answ(n - 1, -1);

	set<int> dontUse;
	while (itr2 != prev(degrees.begin())) {
		int nodeC = itr2->second;
		dontUse.clear();

		for (int i = 0; i < itr2->first; i++) {
			int d = graph.nodes[nodeC].edges[i].dest;
			int index = preA[{nodeC, d}];

			if (answ[index] != -1) {
				dontUse.insert(answ[index]);
			}
		}

		int companyIndex = 1;
		for (int i = 0; i < itr2->first; i++) {
			int d = graph.nodes[nodeC].edges[i].dest;
			int index = preA[{nodeC, d}];

			if (answ[index] == -1) {
				while (dontUse.count(companyIndex) != 0) {
					companyIndex++;
				}
				answ[index] = companyIndex;
				companyIndex++;
			}
		}
		itr2--;
	}

	for (int i = 0; i < n - 1; i++) {
		if (answ[i] == -1) {
			cout << 1 << " ";
		}
		else {
			cout << answ[i] << " ";
		}
	}
	cout << endl;
}