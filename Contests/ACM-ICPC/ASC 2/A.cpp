#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;
typedef long long ll;

string multiply(string num1, string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 == 0 || len2 == 0) { return "0"; }

	vector<int> result(len1 + len2, 0);

	int i_n1 = 0, i_n2 = 0;
	for (int i = len1 - 1; i >= 0; i--) {
		int carry = 0, n1 = num1[i] - '0';
		i_n2 = 0;

		for (int j = len2 - 1; j >= 0; j--) {
			int n2 = num2[j] - '0';
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

			carry = sum / 10; // Carry for next iteration			
			result[i_n1 + i_n2] = sum % 10; // Store result 
			i_n2++;
		}

		if (carry > 0) { result[i_n1 + i_n2] += carry; }
		i_n1++;
	}

	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0) { i--; }

	if (i == -1) { return "0"; }

	string s = "";
	while (i >= 0) { s += std::to_string(result[i--]); }
	return move(s);
}

string add(string a, string b) {
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	while (a.size() < b.size()) { a.push_back('0'); }
	while (b.size() < a.size()) { b.push_back('0'); }

	int n = (int)a.size(), carry = 0; string res = "";
	for (int i = 0; i < n; i++) {
		int x = (a[i] - '0') + (b[i] - '0') + carry;
		if (x < 10) { res.push_back(x + '0'); carry = 0; }
		else { res.push_back(x - 10 + '0'); carry = 1; }
	}
	if (carry == 1) { res.push_back('1'); }
	while (!res.empty() && res.back() == '0') { res.pop_back(); }
	reverse(res.begin(), res.end());
	if (res.empty()) { res = "0"; }
	return move(res);
}

struct edge {
	int u, v; int w; edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w); nodes[u].edges.push_back(e1);
	}

	vector<int> bfs(int u) {
		vector<bool> visited(n, 0);
		vector<int> ans; visited[u] = 1;

		queue<int> Q; Q.push(u);
		queue<int> Q2; Q2.push(u);
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v] || e.w == 1) { continue; }
				visited[e.v] = 1;
				Q.push(e.v); Q2.push(e.v);
			}
		}

		visited.clear(); visited.resize(n, 0);
		while (!Q2.empty()) {
			int cur = Q2.front(); Q2.pop();
			for (auto &e : nodes[cur].edges) {
				if (e.w == 0 || visited[e.v]) { continue; }
				ans.push_back(e.v); visited[e.v] = 1;
			}
		}

		return move(ans);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("dfa.in");
	ofstream ofs("dfa.out");

	string ss; ifs >> ss; int n = (int)ss.size();
	int k; ifs >> k;
	int s, l; ifs >> s >> l; s--;
	vector<int> acc(l);
	for (auto &x : acc) { ifs >> x; x--; }

	vector<vector<int>> transition(k, vector<int>(n)); //State x character
	vector<vector<string>> grid(k, vector<string>(k, "0"));

	vector<graph> vg(n, graph(k));

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			ifs >> transition[i][j]; transition[i][j]--;
		}
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++)
		{
			int tmp; ifs >> tmp;
			vg[j].add_edge(i, transition[i][j], tmp == 0);
		}
	}

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < k; i++) {
			vector<int> reachable = vg[j].bfs(i);
			for (auto &x : reachable) { grid[i][x] = add(grid[i][x], "1"); }
		}
	}

	int N; ifs >> N;

	vector<vector<string>> dp(k, vector<string>(N + 1, "0"));
	dp[s][0] = "1";
	for (int it = 1; it <= N; it++) {
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				if (grid[i][j] == "0") { continue; }
				dp[j][it] = add(dp[j][it], multiply(dp[i][it - 1], grid[i][j]));
			}
		}
	}

	string ans = "0";
	for (auto &a : acc) { ans = add(ans, dp[a][N]); }
	ofs << ans << '\n';
}