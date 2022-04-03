#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <random>
using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, k; cin >> n >> k;
		
		random_device rd;
		mt19937 gen(rd());

		vector<int> cand;
		vector<bool> used(n + 1, false);
		for (int i = 1; i <= n; i++) { cand.push_back(i); }

		int r, p; cin >> r >> p; used[r] = true;
		ll randSampleW = p, neighbSampleW = 0;
		ll numRand = 1, numNeighb = 0;
		int numQuery = 0;
		
		while(numQuery < k && numRand + numNeighb < n) {
			if (n > k) {
				cout << "W" << endl;
				cin >> r >> p;
				if (!used[r]) {
					neighbSampleW += p; numNeighb++;
					used[r] = true;

					if (numRand + numNeighb == n) { break; }
				}
				numQuery++;
				if (numQuery == k) { break; }
			}

			uniform_int_distribution<> dist(0, cand.size() - 1);
			int idx = dist(gen);
			while (used[cand[idx]]) {
				swap(cand[idx], cand.back());
				cand.pop_back();
				
				dist = uniform_int_distribution<>(0, cand.size() - 1);
				idx = dist(gen);
			}

			cout << "T " << cand[idx] << endl;
			cin >> r >> p; 
			
			randSampleW += p; numRand++; 
			used[cand[idx]] = true;
			numQuery++;
		}
		
		ll unknown = (n - numRand - numNeighb);
		ll ans = (randSampleW * (unknown + numRand)) / numRand + neighbSampleW;
		cout << "E " << ans / 2 << endl;
	}
}