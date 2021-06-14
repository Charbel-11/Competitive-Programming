#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int n;
	vector<int> contests;
	cin >> n;
	int temp;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		contests.push_back(temp);
	}

	sort(contests.begin(), contests.end());

	int res = 0;
	int k = 1;
	
	for (int i = 0; i < n; i++) {
		if (contests[i] >= k) {
			res++;
			k++;
		}
		else {
			while (i < n && contests[i] < k) {
				i++;
			}
			if (i == n) { break; }
			res++;
			k++;
		}
	}

	cout << res << endl;
}