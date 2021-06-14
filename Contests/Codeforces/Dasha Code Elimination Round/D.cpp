#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <stack>

using namespace std;

int main() {
	int n, k; cin >> n >> k;

	map<int, stack<int>> wantMe;
	vector<pair<int, int>> guests(k);
	vector<bool> visited(k, 0);
	vector<bool> eaten(n+1, 0);
	map<int, int> freq;
	int sad = 0;
	for (int i = 0; i < k; i++) {
		int a, b; cin >> a >> b;
		guests[i] = { a,b };

		freq[a]++;
		freq[b]++;

		wantMe[a].push(i);
		wantMe[b].push(i);
	}

	queue<int> Q; 
		int start = freq.begin()->first;
		for (int i = 0; i < k; i++) {
			if (guests[i].first == start || guests[i].second == start) {
				if (guests[i].first == start) {
					Q.push(guests[i].first); Q.push(guests[i].second);
				}
				else {
					Q.push(guests[i].second); Q.push(guests[i].first);
				}
				visited[i] = 1; eaten[guests[i].first] = 1; eaten[guests[i].second] = 1;
				break;
			}
		}
	
	int index = 0;

	label:
	while (!Q.empty()) {
		int toEat = Q.front(); Q.pop();

		while (!wantMe[toEat].empty()) {
			int cur = wantMe[toEat].top(); wantMe[toEat].pop();

			if (visited[cur]) { continue; }
			visited[cur] = 1;

			int next = guests[cur].first;
			if (next == toEat) { next = guests[cur].second; }

			if (!eaten[toEat]) { 
				eaten[toEat] = 1; 
				if (!eaten[next]) { Q.push(next); eaten[next] = 1; }
			}
			else if (eaten[next]) { sad++; }
			else {
				eaten[next] = 1;
				Q.push(next);
			}
		}
	}

	for (; index < k; index++) {
		if (!visited[index]) {
			bool b = false;
			if (!eaten[guests[index].first]) {
				Q.push(guests[index].first);
				b = true;
			}
			if (!eaten[guests[index].second]) {
				Q.push(guests[index].second);
				b = true;
			}
			if (!b) {
				visited[index] = 1;
				sad++;
			}
			else { goto label; }
		}
	}

	cout << sad << endl;
}