#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<vector<int>> f(n + 2);
	for (int i = 0; i < n + 2; i++) {
		f[i].resize(m + 2);
		for (int j = 0; j < m + 2; j++) { cin >> f[i][j]; }
	}

	vector<vector<char>> res;
	for (int i = 1; i < n + 1; i++){
		vector<char> foo;
		for(int j = 1; j < m+1; j++){
			if (f[i - 1][j - 1] >= 1) {
				foo.push_back('X');
				for (auto t1 : { -1, 0, 1 })
					for (auto t2 : { -1, 0, 1 })
						f[i + t1][j + t2]--;
			}
			else { foo.push_back('.'); }
		}
		res.push_back(foo);
	}
	for(int i = 0; i < n+2; i++){
		for(int j = 0; j < m+2; j++){
			if (f[i][j] != 0) {
				cout << "impossible" << endl; 
				return 0;
			}
		}
	}

	for(int i = 0; i < n; i++){
		for (int j = 0; j < m; j++) {
			cout << res[i][j];
		}
		cout << endl;
	}
}