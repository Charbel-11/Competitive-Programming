#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;
	
	vector<ll> milestones(1, 1); ll count = 2;
	while(true){
		ll cur = milestones.back(); if (cur > 3e9) { break; }
		cur += count; count++;
		milestones.push_back(cur);
	}

	while (t--) {
		int n, k; cin >> n >> k;
		if (k == 1) {
			string s1(n - 2, 'a'), s2(2, 'b'); 
			cout << s1 << s2 << endl; continue;
		}
		int idx = lower_bound(milestones.begin(), milestones.end(), k) - milestones.begin() + 1;
		string s1(n-idx-1, 'a'); s1.push_back('b');
		int between = milestones[idx-1] - k;
		string s2(between, 'a'); s2.push_back('b');
		string s3(n - s1.size() - s2.size(), 'a');
		cout << s1 << s2 << s3 << endl;
	}
}