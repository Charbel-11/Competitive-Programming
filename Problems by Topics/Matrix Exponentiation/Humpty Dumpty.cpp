// https://acm.timus.ru/problem.aspx?space=1&num=1766

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Matrix {
	int n, m; vector<vector<ld>> v; Matrix() {}
	Matrix(vector<vector<ld>> &_v) : n(_v.size()), m(_v.front().size()), v(_v) {}
	Matrix(int _n, int _m, ld _x) : n(_n), m(_m), v(_n, vector<ld>(_m, _x)) {}
	Matrix(int _n) : n(_n), m(_n), v(_n, vector<ld>(_n, 0)) {
		for (int i = 0; i < _n; i++) { v[i][i] = 1; }
	}
	vector<ld>& operator[](int idx) { return v[idx]; }
	
	Matrix operator *(Matrix &rhs) {
		Matrix res(n, rhs.m, 0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < rhs.m; j++)
				for (int k = 0; k < m; k++)
					res[i][j] = res[i][j] + v[i][k] * rhs[k][j];
		return move(res);
	}
	Matrix operator ^(ll pow2) {
		Matrix res(v);
		for(int i = 0; i < pow2; i++){
			res = res*res;
		}
		return move(res);
	}
	
	Matrix converge(){
		Matrix prev(v), cur(v);
		
		ld EPS = 1e-13;
		while(true){
			cur = cur*cur;
			
			bool changed = false;
			for(int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (abs(prev[i][j] - cur[i][j]) > EPS) {
						changed = true;
						break;
					}
				}
				if (changed) { break; }
			}
			
			if (!changed){ return cur; }
			prev = Matrix(cur.v);
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	ld grid[8][8];
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			cin>>grid[i][j];
	
	vector<vector<ld>> a(64, vector<ld>(64, 0));
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			int cur = i*8+j;
			ld adjSum = 0;
			for(int dx : {-1, 0, 1}){
				for(int dy : {-1, 0, 1}){
					if (dx == 0 && dy == 0){ continue; }
					int ni = i + dx, nj = j + dy;
					if (ni < 0 || ni >= 8 || nj < 0 || nj >= 8){ continue; }
					adjSum += grid[ni][nj];
				}
			}
			for(int dx : {-1, 0, 1}) {
				for (int dy: {-1, 0, 1}) {
					if (dx == 0 && dy == 0) { continue; }
					int ni = i + dx, nj = j + dy;
					if (ni < 0 || ni >= 8 || nj < 0 || nj >= 8) { continue; }
					int curNeighb = ni * 8 + nj;
					a[cur][curNeighb] = grid[ni][nj] / adjSum;
				}
			}
		}
	}
	
	Matrix M(a);
	M = M.converge();
	
	int start = 5*8+3;
	for(int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int cur = i*8+j;
			cout << fixed << setprecision(13) << M[start][cur] << ' ';
		}
		cout << '\n';
	}
}