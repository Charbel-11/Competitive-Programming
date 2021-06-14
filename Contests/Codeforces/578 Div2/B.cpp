#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t;
	cin >> t;

	for (int z = 0; z < t; z++) {
		int n, bagB, k;
		cin >> n >> bagB >> k;
		vector<int> heights(n);
		for (int i = 0; i < n; i++) {
			cin >> heights[i];
		}

		bool OK = true;
		for (int i = 0; i < n - 1; i++) {
			if (heights[i] >= heights[i + 1]) {
				bagB += (heights[i] - heights[i + 1]);
				heights[i] -= (heights[i] - heights[i + 1]);
				
				bagB += min(k, heights[i]);
				heights[i] -= min(k, heights[i]);
			}
			else {
				int dif = heights[i + 1] - heights[i];
				if (dif > k) {
					if (bagB < dif - k) { OK = false; break; }
					else {
						bagB -= dif - k;
					}
				}
				else {
					bagB += min(k - dif, heights[i]);
				}
			}
		}

		if (!OK) { cout << "NO" << endl; }
		else { cout << "YES" << endl; }
	}
}