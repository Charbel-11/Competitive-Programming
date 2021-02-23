#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long ll;

//Queries take O(log^2n) time
struct FT2D {
	int n, m;
	vector<vector<int>> vals;
	FT2D(const int _n, const int _m) :
		n(_n), m(_m), vals(vector<vector<int>>(n + 1, vector<int>(m + 1, 0)))
	{}

	//Adds val to (i,j) 0-indexed
	void update(int i, int j, const int val) {
		i++; j++;
		while (i <= n) {
			int _j = j;
			while (_j <= m) {
				vals[i][_j] += val;
				_j += _j & -_j;
			}
			i += i & -i;
		}
	}

	//Sum of the rectangle (0,0), (i,j)  0-indexed
	int query(int i, int j) const {
		i++; j++;
		int s = 0;
		while (i > 0) {
			int _j = j;
			while (_j > 0) {
				s += vals[i][_j];
				_j -= _j & -_j;
			}
			i -= i & -i;
		}
		return s;
	}

	//Sum of the rectangle (i1,j1) bot-left, (i2,j2) top-right
	int query(int i1, int j1, int i2, int j2) const {
		return query(i2, j2) - query(i2, j1 - 1) - query(i1 - 1, j2) + query(i1 - 1, j1 - 1);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	return 0;
}