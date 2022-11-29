#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//O(root(x))
vector<ll> primeFactors(ll x) {
	vector<ll> ans;
	ll num = 2;
	while (x != 1 && num*num <= x) {
		if (x % num == 0) {
			ans.push_back(num);
			while (x % num == 0) { x /= num; }
		}
		num++;
	}
	if (x != 1) { ans.push_back(x); }
	return ans;
}


//With multiplicity: {prime, multiplicity}
vector<pair<ll, int>> primeFactors(ll x) {
	vector<pair<ll, int>> ans;
	ll num = 2;
	while (x != 1 && num*num <= x) {
		if (x % num == 0) {
			int k = 0;
			while (x % num == 0) {
				x /= num; k++;
			}
			ans.push_back({ num,k });
		}
		num++;
	}
	if (x != 1) { ans.push_back({ x,1 }); }
	return ans;
}

//To get these results for ALL numbers < n, check sieve