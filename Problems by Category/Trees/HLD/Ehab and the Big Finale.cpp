//https://codeforces.com/contest/1174/problem/F

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

//returns dist(u,x)
int queryD(int u) {
	cout << "d " << u + 1 << endl;
	int ans; cin >> ans;
	return ans;
}

//returns next in path from u to x
int queryN(int u) {
	cout << "s " << u + 1 << endl;
	int ans; cin >> ans; ans--;
	return ans;
}

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};
struct node { vector<int> edges; };

struct tree {
	vector<edge> edges;
	vector<node> nodes;
	vector<int> depth, subtreeSize;
	vector<int> chainHead, chainLeaf, chainIdx, base, posInBase;
	int root, n, chainNum, ptr;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		nodes.resize(n); base.resize(n); posInBase.resize(n);
		depth.resize(n, 0); subtreeSize.resize(n, 1);
		chainNum = 0; ptr = 0; 
		chainHead.resize(n, -1); chainLeaf.resize(n, -1); chainIdx.resize(n, 0);
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(edges.size()); edges.push_back(e1);
		nodes[v].edges.push_back(edges.size()); edges.push_back(e2);
	}

	void dfsPre(int u, int p) {
		for (auto &eIdx : nodes[u].edges) {
			auto &e = edges[eIdx];
			if (e.v == p) { continue; }
			depth[e.v] = depth[u] + 1;
			dfsPre(e.v, u);
			subtreeSize[u] += subtreeSize[e.v];
		}
	}

	void hld(int cur, int p) {
		if (chainHead[chainNum] == -1) { chainHead[chainNum] = cur; }
		chainLeaf[chainNum] = cur;
		chainIdx[cur] = chainNum;
		posInBase[cur] = ptr;
		base[ptr++] = cur;

		int idx = -1, maxS = -1, nCost = -1;
		for (auto &eIdx : nodes[cur].edges) {
			auto &e = edges[eIdx];
			if (e.v == p) { continue; }
			if (subtreeSize[e.v] > maxS) {
				maxS = subtreeSize[e.v];
				idx = e.v;
			}
		}

		if (idx >= 0) { hld(idx, cur); }

		for (auto &eIdx : nodes[cur].edges) {
			auto &e = edges[eIdx];
			if (e.v == p || e.v == idx) { continue; }
			chainNum++; hld(e.v, cur);
		}
	}

	int dist(int u, int v) { return depth[v] - depth[u]; }

	int findX() {
		int curR = 0, depthX = queryD(0);
		while (true) {
			int curLeaf = chainLeaf[chainIdx[curR]];
			int distLeafToX = queryD(curLeaf);

			int depthLca = depth[curLeaf] + depthX - distLeafToX; depthLca /= 2;
			int HeadToLca = depthLca - depth[chainHead[chainIdx[curLeaf]]];
			int lca = base[posInBase[curR] + HeadToLca];
			if (depthLca == depthX) { curR = lca; break; }
			curR = queryN(lca);
		}
		return curR;
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	t.dfsPre(0, -1); t.hld(0, -1);
	
	int x = t.findX();
	cout << "! " << x + 1 << endl;
}