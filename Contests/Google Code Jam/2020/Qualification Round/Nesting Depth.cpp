#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
vector<int> leftPar, rightPar, nums;

void form(int count) {
	if (count == 0) { return; }
	int i = 0;
	while(i<n){
		if (nums[i] == count) { 
			nums[i]--; leftPar[i]++; i++;
			while (i < n && nums[i] == count) {
				nums[i]--; i++;
			}
			rightPar[i - 1]++;
		}
		else { i++; }
	}
	form(count - 1);
}

int main() {
	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		string s; cin >> s; n = s.size(); int mm = 0;

		leftPar.clear(); rightPar.clear(); nums.clear();
		leftPar.resize(n, 0); rightPar.resize(n, 0); nums.resize(n, 0);
		for (int i = 0; i < n; i++) { nums[i] = s[i] - '0'; mm = max(mm, nums[i]); }
		vector<int> input = nums;
		form(mm);

		cout << "Case #" << q << ": ";
		for (int i = 0; i < n; i++) {
			while (leftPar[i]--) { cout << '('; }
			cout << input[i];
			while (rightPar[i]--) { cout << ')'; }
		}
		cout << endl;
	}
}