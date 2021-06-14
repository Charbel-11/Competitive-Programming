#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> indices;
vector<pair<int, int>> answ;
vector<int> nums;
int n;

void doIt(int i, int realIndex) {
	int temp = nums[i];
	nums[i] = nums[realIndex];
	nums[realIndex] = temp;

	answ.push_back({ i, realIndex });
}

int Swap(int i) {
	if (i >= indices.size()) {
		return 0;
	}

	int realIndex = indices[i];
	if (realIndex == i) {
		return Swap(i + 1);
	}

	if (realIndex - i >= n / 2) {
		indices[nums[i]-1] = realIndex;
		
		doIt(i, realIndex);
		return 1 + Swap(i + 1);
	}

	int bigT = realIndex + n / 2;

	if (bigT < n) {
		indices[nums[i]-1] = bigT;
		indices[nums[bigT]-1] = realIndex;

		doIt(realIndex, bigT);
		doIt(i, bigT);

		return 2 + Swap(i + 1);
	}

	int smallT = i - n / 2;
	if (smallT >= 0) {
		indices[nums[i]-1] = realIndex;
		
		doIt(smallT, realIndex);
		doIt(smallT, i);
		doIt(smallT, realIndex);

		return 3 + Swap(i + 1);
	}

	int T = realIndex - n / 2;

	indices[nums[i]-1] = i + n / 2;
	indices[nums[i + n / 2]-1] = realIndex;

	doIt(T, realIndex);
	doIt(T, i + n / 2);
	doIt(i, i + n / 2);
	doIt(T, realIndex);

	return 4 + Swap(i + 1);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n;

	indices = vector<int>(n);
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		nums.push_back(t);
		indices[t-1] = i;
	}

	int res = Swap(0);

	cout << res << endl;
	for (int i = 0; i < res; i++) {
		cout << answ[i].first+1<< " " << answ[i].second+1 << endl;
	}
}