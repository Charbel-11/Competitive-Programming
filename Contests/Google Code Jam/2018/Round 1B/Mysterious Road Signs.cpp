#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct sign {
	int D, A, B;

	sign(int d, int a, int b) : D(d), A(a), B(b) {}
};

int S;
vector<sign> signs;

int main() {
	int T; cin >> T;

	for (int z = 1; z <= T; z++) {
		cin >> S; signs.clear();
		for (int i = 0; i < S; i++) {
			int d, a, b; cin >> d >> a >> b;
			signs.push_back(sign(d,a,b));
		}

		map<int, vector<int>> M;
		map<int, set<int>> N;
		map<int, int> Nsize;	//N size -> how many N
		for (int i = 0; i < S; i++) {
			M[signs[i].D + signs[i].A].push_back(i);
			int newN = signs[i].D - signs[i].B;
			if (N.count(newN)) { Nsize[N[newN].size()]--; }
			N[newN].insert(i);
			Nsize[N[newN].size()]++;
		}
		
		int maxAns = 0, rep = 0;
		for (auto &m : M) {
			auto &v = m.second;
			int curAns = v.size(), curRep = 0;
			
			for (auto &i : v) {
				int curN = signs[i].D - signs[i].B;
				Nsize[N[curN].size()]--;
				if (Nsize[N[curN].size()] == 0) { Nsize.erase(N[curN].size()); }
				N[curN].erase(i);
				if (N[curN].empty()) { N.erase(curN); }
				else { Nsize[N[curN].size()]++; }
			}

			if (!Nsize.empty()) {
				curAns += (*(--Nsize.end())).first;
				curRep += (*(--Nsize.end())).second;
			}
			if (maxAns < curAns) {
				maxAns = curAns;
				rep = max(curRep, 1);
			}

			for (auto &i : v) {
				int curN = signs[i].D - signs[i].B;
				Nsize[N[curN].size()]++;
				N[curN].insert(i);
				Nsize[N[curN].size()]--;
				if (Nsize[N[curN].size()] == 0) { Nsize.erase(N[curN].size()); }
			}
		}

		cout << "Case #" << z << ": " << maxAns << " " << rep << endl;
	}
}