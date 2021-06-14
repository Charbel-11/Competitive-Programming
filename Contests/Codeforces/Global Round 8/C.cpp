#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	int i = 1e4, j = 0;

	vector<pair<int, int>> ans;

	ans.push_back({ i,j });
	ans.push_back({ i,j +1});
	ans.push_back({ i-1,j });
	ans.push_back({ i-1,j+1 });

	i--; j++; n--;
	while (n) {
		ans.push_back({ i,j + 1 });
		ans.push_back({ i,j + 2 });
		ans.push_back({ i - 1,j });
		ans.push_back({ i - 2,j });
		ans.push_back({ i - 2,j + 1 });
		ans.push_back({ i - 2,j + 2 });
		ans.push_back({ i - 1, j + 2 });
		i -= 2; j += 2; n--;
	}

	ans.push_back({ i,j + 1 });
	ans.push_back({ i - 1,j });
	ans.push_back({ i - 1,j + 1 });

	cout << ans.size() << '\n';
	for (auto &p : ans) { cout << p.first << ' ' << p.second << '\n'; }
}