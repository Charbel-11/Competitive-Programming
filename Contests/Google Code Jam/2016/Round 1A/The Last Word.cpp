#include <fstream>
#include <deque>
#include <string>

using namespace std;

int main() {
	ifstream ifs ("in.in");
	ofstream ofs ("out.txt");

	int T; ifs >> T;
	for (int z = 0; z < T; z++) {
		string S; ifs >> S;
		deque<char> ans;
		for (char &c : S) {
			if (ans.empty()) { ans.push_back(c); continue; }
			if (ans[0] > c) { ans.push_back(c); }
			else { ans.push_front(c); }
		}
		ofs << "Case #" << z + 1 << ": ";
		for (auto &x : ans) { ofs << x; }
		ofs << endl;
	}
}