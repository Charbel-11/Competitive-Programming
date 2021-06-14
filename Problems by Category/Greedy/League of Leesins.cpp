#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
	int n; cin >> n;
	vector<bool> visited(n + 1, 0);
	vector<int> res(n);

	map<int, int> freq;
	multimap<pair<int, int>, int> m;

	for (int i = 0; i < n - 2; i++) {
		int a, b, c; cin >> a >> b >> c;
		freq[a]++; freq[b]++; freq[c]++;
		
		m.insert({ { a, b }, c });
		m.insert({ { b, a }, c });
		m.insert({ { a, c }, b });
		m.insert({ { c, a }, b });
		m.insert({ { c, b }, a });
		m.insert({ { b, c }, a });
	}

	bool f1 = false;
	for (auto &x : freq) {
		if (x.second == 1) { 
			visited[x.first] = true;
			if (!f1) { res[0] = x.first; f1 = true; }
			else res[n - 1] = x.first;
		}
	}
	for (auto &x : m) {
		if (x.first.first == res[0] && freq[x.first.second] == 2) { 
			res[1] = x.first.second; 
			visited[x.first.second] = true; 
		}
		else if (x.first.first == res[n - 1] && freq[x.first.second] == 2) {
			res[n - 2] = x.first.second; 
			visited[x.first.second] = true;
		}
	}

	int i = 2;
	while (i < n - 2) {
		pair<int, int> p = { res[i - 2], res[i - 1] };
		auto it = m.find(p);
		if (visited[it->second]) { 
			m.erase(it); it = m.find(p);
		}

		visited[it->second] = true;
		res[i] = it->second;
		i++;
	}

	for (auto &x : res) { cout << x << " "; }cout << endl;
}