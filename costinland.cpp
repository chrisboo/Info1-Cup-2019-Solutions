#include <iostream>
using namespace std;

int MAXN = 49;

long long K, f[100];
char mat[50][50];

int main() {

	cin >> K;

	if (K <= 19)
		MAXN = 5;

	for (int r = 1; r + 2 < MAXN; r++) {
		mat[r][r-1] = 'r';
		mat[r][r+2] = 'd';
	}

	for (int i = 0; i < MAXN; i++) {
		mat[MAXN-1][i] = 'r';
		mat[i][MAXN-1] = 'd';
	} mat[MAXN-1][MAXN-1] = '.';

	mat[0][0] = mat[0][1] = 'X'; mat[0][2] = 'd';

	f[0] = 1; f[1] = 1; long long cnt = 3; int i = 2;
	for (;; i++) {
		f[i] = f[i-1] + f[i-2];

		if (cnt + f[i] > K)
			break;

		int r = i / 2;
		int c = r + i % 2;
		mat[r][c] = 'X';

		cnt += f[i];
	}

	K -= cnt;

	for (; i > 0; i--) {
		if (K >= f[i]) {
			K -= f[i];

			int r = i / 2;
			int c = r + i % 2;
						
			if (i % 2 == 0) {
				mat[r+1][c] = 'X';
			} else {
				mat[r][c+1] = 'X';
			}
		}
	}

	cout << MAXN << " " << MAXN << endl;
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			cout << (mat[i][j] ? mat[i][j] : '.') ;
		} cout << endl;
	}

	return 0;
}