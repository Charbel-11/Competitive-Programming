#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Some test cases didn't work

//Smallest sum of val_i*b_j is when val is in order and b in reverse order
//Here we can't take val_i to be a_i since we are multiplying the product by (i+1)*(n-i)

int main() {
	int n; 
	cin >> n;
	vector<long long> a(n);
	vector<long long> b(n);
	vector<long long> val(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	sort(b.rbegin(), b.rend());             //reverse sort

	for (int i = 0; i < n; i++) {
		val[i] = (a[i] * 1ll * (i + 1)*(n - i));
	}
	sort(val.begin(), val.end());		

	long long res = 0;

	for (int i = 0; i < n; i++) {
		res += (val[i] * b[i]) % 998244353;
		res = res % 998244353;				//Take mod again
	}

	cout << res << endl;
}