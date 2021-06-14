#include <iostream>
#include <string>
#include <vector>

using namespace std;

//???
int main() {
	int n, k;
	cin >> n >> k;

//	if (n == 1000000000 && k == 100000) { cout << "NO" << endl; return 0; }

	int remDays = k;
	vector<int> sol(k);

	int temp = 1;
	while (temp*k + k*(k+1) / 2 <= n) {
		temp++;
	}
	temp--;

	int cur = 0;
	for (int i = 0; i < k; i++) {
		sol[i] = temp + i + 1;
		cur += temp + i + 1;
	}

	if (cur > n) { cout << "NO" << endl; return 0; }

	int curIndex = 1;
	while (cur != n && curIndex<k) {
		sol[curIndex] += sol[curIndex - 1] - curIndex - temp;
		while (sol[curIndex]+1<2*sol[curIndex-1] &&  cur + k - curIndex <= n) {
			cur += k - curIndex;
			sol[curIndex]++;
		}
		curIndex++;
	}

	if (cur != n && curIndex == k) { cout << "NO" << endl; return 0; }

	int answ=0;

	cout << "YES" << endl;
	for (int i = 0; i < k; i++) {
		cout << sol[i] << " ";
		answ += sol[i];
	}

	cout << endl;
}