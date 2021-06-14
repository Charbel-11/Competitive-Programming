#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("input.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;

	for (int qq = 1; qq <= t; qq++) {
		ll N, K; ifs >> N >> K;
		vector<ll> S(N), X(N), Y(N);
		ll totS = 0, totX = 0, totY = 0;

		for (int i = 0; i < K; i++) { ifs >> S[i]; totS += S[i]; }
		ll AS, BS, CS, DS; ifs >> AS >> BS >> CS >> DS;
		for (int i = K; i < N; i++) {
			S[i] = AS * S[i - 2]; S[i] %= DS;
			S[i] += BS * S[i - 1]; S[i] %= DS;
			S[i] += CS; S[i] %= DS;
			totS += S[i];
		}

		for (int i = 0; i < K; i++) { ifs >> X[i]; totX += X[i]; }
		ll AX, BX, CX, DX; ifs >> AX >> BX >> CX >> DX;
		for (int i = K; i < N; i++) {
			X[i] = AX * X[i - 2]; X[i] %= DX;
			X[i] += BX * X[i - 1]; X[i] %= DX;
			X[i] += CX; X[i] %= DX;
			totX += X[i];
		}

		for (int i = 0; i < K; i++) { ifs >> Y[i]; totY += Y[i]; }
		ll AY, BY, CY, DY; ifs >> AY >> BY >> CY >> DY;
		for (int i = K; i < N; i++) {
			Y[i] = AY * Y[i - 2]; Y[i] %= DY;
			Y[i] += BY * Y[i - 1]; Y[i] %= DY;
			Y[i] += CY; Y[i] %= DY;
			totY += Y[i];
		}
		for (int i = 0; i < N; i++) { Y[i] += X[i]; }
		totY += totX;

		ofs << "Case #" << qq << ": ";
		if (totS < totX || totS > totY) { ofs << -1 << '\n'; continue; }

		ll neededToAdd = 0, neededToRem = 0;
		for (int i = 0; i < N; i++) {
			if (S[i] < X[i]) { neededToAdd += (X[i] - S[i]); }
			else if (S[i] > Y[i]) { neededToRem += (S[i] - Y[i]); }
		}
		ll ans = min(neededToAdd, neededToRem);
		neededToAdd -= ans; neededToRem -= ans;
		ans += (neededToAdd + neededToRem);

		ofs << ans << '\n';
	}
}