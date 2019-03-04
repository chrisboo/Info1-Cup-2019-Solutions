#include <iostream>
#include <cstdlib>

#include "grader.h"
using namespace std;

int kth(int k);
void say_answer(int k);
int cnt(int k);

int N;

void solve(int N) {

	int k = (N <= 50 ? 25 : 30);
	
	int ans = -1;
	for (int i = 0; i < k; i++) {
		int v = kth((rand() % N) + 1);
		int f = cnt(v);

		if (3 * f > N) {
			ans = v;
		}
	}

	say_answer(ans);
}
