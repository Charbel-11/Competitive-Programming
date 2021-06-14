#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>

using namespace std;

struct edge_t{
	int dest;
	int weight;
	
	edge_t() {}
	edge_t(int ad, int aw=0): dest(ad), weight(aw) {}
};

struct node_t{
	int name;
	vector<edge_t> edges;
	int color;
	
	node_t() {}
	node_t(int an): name(an), color(-1) {}
};

struct graph_t{
	map<int, node_t> nodes;
	
	int color(int node);
};

int graph_t::color(int node = 1){
	set<int> visited;
	queue<int> Q;
	
	nodes[node].color = 0;
	Q.push(node);
	visited.insert(node);

	while (!Q.empty()){
		int v = Q.front();
		Q.pop();
		
		if (nodes.count(v) == 0) { return -1; }
	
		node_t& n = nodes[v];
		for(int i = 0; i < n.edges.size(); i++){
			edge_t& e = n.edges[i];
			
			//If the node is not visited
			if (visited.find(e.dest) == visited.end()){
				if (n.color==0){
					nodes[e.dest].color = 1;
				}
				else{
					nodes[e.dest].color = 0;
				}
				Q.push(e.dest);
				visited.insert(e.dest);
			}
			else{
				if (n.color == nodes[e.dest].color){
					return -1;
				}
			}
		}
	}
	
	return 1;
}

int main(){
	int n, m;
	cin >> n >> m;

	graph_t graph;
	for (int i = 0; i < n; i++) {			//create nodes
		graph.nodes[i + 1] = node_t(i + 1);
	}

	vector<pair<int, int>> uv;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		
		uv.push_back({ u, v });
		graph.nodes[u].edges.push_back(edge_t(v));
		graph.nodes[v].edges.push_back(edge_t(u));	//since undirected
	}

	int res = graph.color();

	if (res == -1) {
		cout << "NO" << endl;
	}
	else {
		cout << "YES" << endl;

		for (int i = 0; i < uv.size(); i++) {
			cout << graph.nodes[uv[i].second].color;
		}
		cout << endl;
	}
}