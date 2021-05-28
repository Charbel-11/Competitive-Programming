//https://csacademy.com/contest/archive/task/matching-substrings
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <string>
using namespace std;

int start;

struct edge {
	int u, v; char c; edge() {}
	edge(int _u, int _v, char _c) :
		u(_u), v(_v), c(_c) {}
};

struct node { int inD = 0, outD = 0; vector<int> edges; };

//Goes over all edges, not necessarily all vertices
struct graph {
	vector<edge> edges;
	vector<node> nodes;
	int n, m;
	graph(int _n) : n(_n), m(0) { nodes.resize(n); }

	void add_edge(int u, int v, char c) {
		nodes[u].edges.push_back(m++);
		nodes[u].outD++; nodes[v].inD++;
		edges.push_back(edge(u, v, c));
	}

	//Start can be any node; if it has to be 0 we should add a check
	//Since node 0 could have 0 edges and start becomes 1 for ex
	vector<char> euler_directed() {
		start = -1; int oddIn = 0, oddOut = 0;
		for (int i = 0; i < n; ++i) {
			int diff = nodes[i].inD - nodes[i].outD;
			if (abs(diff) > 1) { return vector<char>(); }
			if (diff == -1) { oddOut++; start = i; }
			else if (diff == 1) { oddIn++; }
			else if (diff == 0 && start == -1) { start = i; }
		}

		//if (oddOut || oddIn) { return vector<int>(); }	//No Euler Cycle
		if (oddOut > 1 || oddIn > 1) { return vector<char>(); }	//No Euler Path
		vector<bool> used(m, 0);
		vector<pair<int, char>> stack;
		vector<char> res;
		vector<int> which(n + 1, 0);		//which[v] = index of the edge with endpoint v to check next
		stack.push_back({ start,'%' });
		while (!stack.empty()) {
			int v = stack.back().first; char c = stack.back().second;
			while (which[v] < (int)nodes[v].edges.size() && used[nodes[v].edges[which[v]]]) { which[v]++; }
			if (which[v] == (int)nodes[v].edges.size()) {
				stack.pop_back(); 
				if (c != '%') { res.push_back(c); }
			}
			else {
				int ed = nodes[v].edges[which[v]];
				int w = (edges[ed].u) == v ? edges[ed].v : edges[ed].u;
				used[ed] = 1; stack.push_back({ w,edges[ed].c });
			}
		}
		if (count(used.begin(), used.end(), false)) { return vector<char>(); }	//Not all edges were reachable
		reverse(res.begin(), res.end());
		return move(res);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, k; cin >> n >> k;
	map<string, int> words; //str[1..K] -> freq
	map<string, int> m;		//str[1..K-1] -> idx
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		words[s]++;
		string s2 = s; s2.pop_back();
		m[s2] = 1;
		string s3 = s; reverse(s3.begin(), s3.end());
		s3.pop_back(); reverse(s3.begin(), s3.end());
		m[s3] = 1;
	}

	if (k == 1) { 
		for (auto &c : words) { 
			for(int j = 0; j < c.second; j++)
				cout << c.first;
		} 
		return 0; 
	}

	int idx = 0;
	for (auto &it : m) { it.second = idx++; }
	graph g(idx);
	for (auto &it : m) {
		string curS = it.first;
		string endS = it.first; reverse(endS.begin(), endS.end());
		endS.pop_back(); reverse(endS.begin(), endS.end());
		for (int i = 0; i < 26; i++) {
			char curC = 'a' + i;
			curS.push_back(curC);
			endS.push_back(curC);
			int rep = words[curS];
			for (int j = 0; j < rep; j++) {
				g.add_edge(it.second, m[endS], curC);
			}
			curS.pop_back();
			endS.pop_back();
		}
	}

	vector<char> ans = g.euler_directed();
	if (ans.empty()) { cout << -1 << '\n'; return 0; }
	for (auto &it : m) {
		if (it.second == start) { cout << it.first; break; }
	}
	for (auto &c : ans) { cout << c; }
}