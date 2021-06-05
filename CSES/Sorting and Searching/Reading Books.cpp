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
	vector<ll> t(n); for (auto &x : t) { cin >> x; }
	sort(t.begin(), t.end());

	ll ss = 0;
	for (int i = 0; i < n - 1; i++) { ss += t[i]; }
	
	if (ss < t.back()) { ss = t.back(); }
	ss += t.back();

	cout << ss << '\n';
}

//Proof: if max > sum/2 then obviously the answer is max*2
//Otherwise, we can 'group' the others into 3 books where no book has a time > sum/2
//To do so, keep adding the books until we get >= n/2, remove the last one added now we have 2 groups
//The remaining books (which must exist since max <= sum/2) form the 3rd group
//Now that we have 3 books, A, B, C where A>B>C
//The 1st person starts with A and the 2nd with B. The 2nd finishes first and goes to C
//Once the second finishes C, A must have been freed and he ends with A (since B+C>A)
//Once the first finishes A, B is empty since A>B. Once he finishes B, C is empty since A+B > B+C