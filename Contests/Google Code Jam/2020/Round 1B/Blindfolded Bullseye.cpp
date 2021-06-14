#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int T, A, B; cin >> T >> A >> B;
	for (int q = 1; q <= T; q++) {
		int firstTry = 1000 * 1000 * 500;
		int x, y; bool done = false, enough = false;
		for (auto c1 : { -1,1 }) {
			for (auto c2 : { -1,1 }) {
				cout << firstTry * c1 << " " << firstTry * c2 << endl;
				string s; cin >> s;
				if (s == "MISS") { continue; }
				if (s == "CENTER") { done = true; break; }
				x = firstTry * c1; y = firstTry * c2;
				enough = true; break;
			}
			if (done || enough) { break; }
		}
		if (done) { continue; }
		cout << 0 << " " << 0 << endl;
		string sss; cin >> sss;
		if (sss == "HIT") { x = y = 0; }

		int l = x, r = (int)1e9;
		while (l < r) {
			int mid;
			if (l + r > 0) { mid = (l + r + 1) / 2; }
			else { mid = (l + r) / 2; } 

			cout << mid << " " << y << endl;
			string s; cin >> s;
			if (s == "CENTER") { done = true; break; }
			if (s == "MISS") { r = mid - 1; }
			else { l = mid; }
		}
		if (done) { continue; }
		pair<int, int> rightPoint = { l, y };

		l = -((int)1e9), r = rightPoint.first;
		while (l < r) {
			int mid;
			if (l + r > 0) { mid = (l + r) / 2; }
			else { mid = (l + r - 1) / 2; }
			
			cout << mid << " " << y << endl;
			string s; cin >> s;
			if (s == "CENTER") { done = true; break; }
			if (s == "MISS") { l = mid + 1; }
			else { r = mid; }
		}
		if (done) { continue; }
		pair<int, int> leftPoint = { l,y };

		cout << (leftPoint.first + rightPoint.first) / 2 << " " << leftPoint.second << endl;
		string s2; cin >> s2;
		if (s2 == "CENTER") { continue; }

		bool goTop = false;
		cout << (leftPoint.first + rightPoint.first) / 2 << " " << leftPoint.second + 1 << endl;
		cin >> s2;
		if (s2 == "CENTER") { continue; }
		if (s2 == "HIT") { goTop = true; }

		pair<int, int> point3;
		if (goTop) {
			int d = leftPoint.second, u = (int)1e9;
			while (d < u) {
				int mid;
				if (d + u > 0) { mid = (d + u + 1) / 2; }
				else { mid = (d + u) / 2; }

				cout << leftPoint.first << " " << mid << endl;
				string s; cin >> s;
				if (s == "CENTER") { done = true; break; }
				if (s == "MISS") { u = mid - 1; }
				else { d = mid; }
			}
			point3 = { leftPoint.second, d };
		}
		else {
			int d = -((int)1e9), u = leftPoint.second;
			while (d < u) {
				int mid;
				if (d + u > 0) { mid = (d + u) / 2; }
				else { mid = (d + u - 1) / 2; }

				cout << leftPoint.first << " " << mid << endl;
				string s; cin >> s;
				if (s == "CENTER") { done = true; break; }
				if (s == "MISS") { d = mid + 1; }
				else { u = mid; }
			}
			point3 = { leftPoint.second, d };

		}
		if (done) { continue; }

		int possibleX = (leftPoint.first + rightPoint.first) / 2;
		int possibleY = (leftPoint.second + point3.second) / 2;

		for (int i = -5; i < 5; i++) {
			for (int j = -5; j < 5; j++) {
				int curX = possibleX + i, curY = possibleY + j;
				if (curX < -((int)1e9) || curY < -((int)1e9)) { continue; }
				if (curX > ((int)1e9) || curY > ((int)1e9)) { continue; }
				cout << curX << " " << curY << endl;
				string dd; cin >> dd;
				if (dd == "CENTER") { done = true; break; }
			}
			if (done) { break; }
		}
	}
	return 0;
}