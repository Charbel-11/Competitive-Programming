#include <iostream>

using namespace std;
typedef long long ll;

int main() {
	int T, W; cin >> T >> W;

	for(int qq = 1; qq <= T; qq++){
		cout << "227" << endl;
		cout.flush();
		ll q1; cin >> q1;
		ll ans[7];
		ans[4] = (q1 >> 56) & 127;
		ans[5] = (q1 >> 45) & 127;
		ans[6] = (q1 >> 37) & 127;

		cout << "56" << endl;
		cout.flush();
		ll q2; cin >> q2;
		q2 -= ans[4] << 14; q2 -= ans[5] << 11; q2 -= ans[6] << 9;
		ans[1] = (q2 >> 56) & 127;
		ans[2] = (q2 >> 28) & 127;
		ans[3] = (q2 >> 18) & 127;

		for (int i = 1; i < 7; i++) { cout << ans[i] << ' '; }
		cout << endl;
		cout.flush();
		int verd; cin >> verd; 
		if (verd == -1) { return 0; }
	}
	return 0;
}