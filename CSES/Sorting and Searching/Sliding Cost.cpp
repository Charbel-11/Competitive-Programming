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

	int n, k; cin >> n >> k;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	int mid = (k % 2 ? k / 2 : k / 2 - 1), cur;

	ll sumB = 0, sumS = 0;
	multiset<int> smaller, bigger;

	vector<int> temp;
	for (int i = 0; i < k; i++) { temp.push_back(nums[i]); }
	sort(temp.begin(), temp.end());

	for (int i = 0; i <= mid; i++) { sumS += temp[i]; smaller.insert(temp[i]); }
	for (int i = mid + 1; i < k; i++) { sumB += temp[i]; bigger.insert(temp[i]); }
	int sizeB = (int)bigger.size(), sizeS = (int)smaller.size();
	cur = *(prev(smaller.end()));
	cout << sumB - (ll)sizeB*cur + (ll)sizeS*cur - sumS << ' ';

	for (int i = k; i < n; i++) {
		if (nums[i - k] <= cur) { sumS -= nums[i - k]; smaller.erase(smaller.find(nums[i - k])); }
		else { sumB -= nums[i - k]; bigger.erase(bigger.find(nums[i - k])); }

		if (nums[i] <= cur) { sumS += nums[i]; smaller.insert(nums[i]); }
		else { sumB += nums[i]; bigger.insert(nums[i]); }

		while (smaller.size() < bigger.size()) {
			sumS += *bigger.begin();
			sumB -= *bigger.begin();
			smaller.insert(*bigger.begin());
			bigger.erase(bigger.begin());
		}
		while (smaller.size() > bigger.size() + 1) {
			sumB += *prev(smaller.end());
			sumS -= *prev(smaller.end());
			bigger.insert(*prev(smaller.end()));
			smaller.erase(prev(smaller.end()));
		}
		cur = *(prev(smaller.end()));
		cout << sumB - (ll)sizeB*cur + (ll)sizeS*cur - sumS << ' ';
	}
}