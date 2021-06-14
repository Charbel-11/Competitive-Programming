#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;
typedef long long ll;

unordered_map<string, int> decode = { {"1110111",0},{"0010010",1},{"1011101",2},{"1011011",3},{"0111010",4}
,{"1101011",5},{"1101111",6},{"1010010",7},{"1111111",8},{"1111011",9} };
unordered_map<int, string> encode = { {0,"1110111"},{1,"0010010"},{2,"1011101"},{3,"1011011"},{4,"0111010"}
,{5,"1101011"},{6,"1101111"},{7,"1010010"},{8,"1111111"},{9,"1111011"} };

bool dp[2002][2002];
int choice[2002][2002];
int cost[2002][10];
vector<string> nums;

int findCost(int i, int d) {
	if (cost[i][d] != -2) { return cost[i][d]; }
	string &target = encode[d]; int ans = 0;
	for (int j = 0; j < 7; j++) {
		if (nums[i][j] == '1' && target[j] == '0') { return cost[i][d]=-1; }
		else if (nums[i][j] == '0' && target[j] == '1') { ans++; }
	}
	return cost[i][d] = ans;
}

bool best(int i, int k) {
	if (choice[i][k] != -1) { return dp[i][k]; }
	if (i == nums.size()) { return k == 0; }

	bool possible = false;
	for (int d = 9; d >= 0; d--) {
		int cc = findCost(i, d);
		if (cc > k || cc == -1) { continue; }
		bool next = best(i + 1, k - cc);
		if (next) { possible = true; choice[i][k] = d; break; }
	}

	if (choice[i][k] == -1) { choice[i][k] = -2; dp[i][k] = 0; }

	return possible;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	for (int i = 0; i < 2002; i++)
		for (int j = 0; j < 2002; j++)
			choice[i][j] = -1;

	for (int i = 0; i < 2002; i++)
		for (int j = 0; j < 10; j++)
			cost[i][j] = -2;
	//memset?

	int n, k; cin >> n >> k;
	nums.resize(n);
	for (auto &s : nums) { cin >> s; }
	
	bool b = best(0, k);
	if (!b) { cout << -1 << endl; return 0; }

	for (int i = 0; i < n; i++) {
		cout << choice[i][k];
		k -= cost[i][choice[i][k]];
	}
	cout << endl;
}