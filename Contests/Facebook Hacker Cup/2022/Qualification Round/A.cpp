#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
        int n, k; ifs >> n >> k;
        vector<int> S(n); for(auto &x : S){ ifs >> x; }

        if (n > 2 * k){
            ofs << "Case #" << qq << ": NO" << '\n';
            continue;
        }

        bool OK = true;
        vector<int> freq(105, 0);
        for(auto &x : S){
            freq[x]++;
            if (freq[x] > 2){
                OK = false; break;
            }
        }

        if (OK){
            ofs << "Case #" << qq << ": YES" << '\n';
        }
        else{
            ofs << "Case #" << qq << ": NO" << '\n';
        }
	}
}