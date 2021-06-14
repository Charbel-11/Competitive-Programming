#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("matrix.in");
	ofstream ofs("matrix.out");

	int N, M; ifs >> N >> M;
	vector<int> occ(N, 0);
	for (int i = 0; i < M; i++) {
		int u, v; ifs >> u >> v;
		u--; v--;
		occ[u]++; occ[v]++;
	}

	ll res = 0;
	for (int i = 0; i < N; i++) {
		res += (ll)occ[i] * occ[i];
	}

	ofs << res << '\n';
}