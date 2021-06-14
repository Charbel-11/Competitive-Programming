#include <iostream>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct node_t {
	int name;
	set<int> edges;

	node_t() {}
	node_t(int an) : name(an) {}
};

vector<node_t> nodes;
vector<int> visited;		//stores the component number of each node; no need to clear it at any point; waste of a lot of time
vector<int> shared;			//stores the result of each component

int dfs(int node, int comp) {
	stack<int> S;

	visited[node] = comp;
	S.push(node);
	int res = 1;

	while (!S.empty()) {
		int curNodeIn = S.top();
		node_t curNode = nodes[curNodeIn];
		S.pop();

		for (int e : curNode.edges) {
			if (visited[e] == -1) {
				res++;
				visited[e] = comp;
				S.push(e);
			}
		}
	}

	return res;
}

int main() {
	int n, m;
	cin >> n >> m;

	if (m == 1) {
		int k;
		cin >> k;
		if (k == n) {
			for (int i = 0; i < n; i++) {
				cout << n << " ";
			}
			cout << endl;
			return 0;
		}
	}

	nodes.resize(n + 1);
	for (int i = 0; i < n + 1; i++) {			//create nodes (0 for convenience, won't be used)
		nodes[i] = node_t(i);
	}

	visited.resize(n + 1, -1);
	shared.resize(n + 1);

	for (int i = 0; i < m; i++) {
		int k;
		cin >> k;
		vector<int> temp(k);
		for (int j = 0; j < k; j++) {
			cin >> temp[j];
		}

		//We don't need to conect all nodes together, just making them reachable from each other is enough
		//It brings down the complexity from quadratic to linear
		for (int j = 0; j < k - 1; j++) {
			nodes[temp[j]].edges.insert(temp[j + 1]);		//If it is already existant, it doesn't get added another time
			nodes[temp[j + 1]].edges.insert(temp[j]);
		}
	}

	int comp = 0;
	for (int i = 1; i < n + 1; i++) {			//starts at node 1
		if (visited[i] == -1) {
			shared[comp] = dfs(i, comp);
			comp++;
		}
		cout << shared[visited[i]] << " ";
	}
	cout << endl;
}