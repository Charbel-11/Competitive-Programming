#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a%b);
}

void normalize(pair<int, int>& p) {
	if (p.first < 0) {
		p.first *= -1;
		p.second *= -1;
	}
	else if (p.first == 0) {
		p.second = 0;
	}

	int g = gcd(abs(p.first), abs(p.second));
	if (g != 1) {
		p.first /= g;
		p.second /= g;
	}
}

int main() {
	int n;
	cin >> n;
	vector<double> a(n);
	vector<double> b(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	map<pair<int, int>, int> freq;			//unordered map doesn't hash pairs

	int added = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 0 && b[i] == 0) {
			added++;
			continue;
		}
		if (a[i] == 0) {
			continue;
		}

		pair<int, int> p = { -b[i], a[i] };
		normalize(p);
		
		if (freq.count(p) == 0) {
			freq.insert({ p, 1 });
		}
		else {
			freq[p]++;
		}
	}

	map<pair<int, int>, int>::iterator itr = freq.begin();
	if (itr == freq.end()) {
		cout << added << endl;
		return 0;
	}
	int maxFreq = itr->second;
	itr++;
	while (itr != freq.end()) {
		if (itr->second > maxFreq) {
			maxFreq = itr->second;
		}
		itr++;
	}

	cout << maxFreq + added << endl;
}