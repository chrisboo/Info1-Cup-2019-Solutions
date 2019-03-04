#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 200005;

int T, N;
int a[MAXN], pos[MAXN];

vector<int> x, y;

void swap2(int i, int j) {
    pos[a[i]] = j;
    pos[a[j]] = i;

    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void swap(int i, int j) {
    x.push_back(i);
    y.push_back(j);

    swap2(i, j);
    swap2(N+1-i, N+1-j);
}

int main() {

    scanf("%d", &T);
    while (T--) {

        x.clear();
        y.clear();

        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            scanf("%d", &a[i]);
        
            pos[a[i]] = i;
        }

        stack<int> wait;

        bool possible = true;
        for (int i = 1; i <= N / 2; i++) {
            if (a[i] == i && a[N+1-i] == N+1-i)
                continue;

            if (pos[i] - i != N+1-i - pos[N+1-i]) {
                possible = false;
                break;
            }

            if (a[i] == N+1-i) {
                wait.push(i);
            } else {
                swap(i, pos[i]);
            }
        }

        if (wait.size() % 2 != 0) {
            possible = false;
        } 

        if (!possible) {
            printf("-1\n");
            continue;
        }

        while (!wait.empty()) {
            int i = wait.top(); wait.pop();
            int j = wait.top(); wait.pop();
            swap(i, j);
            swap(i, N+1-j);
        }

        int cnt = x.size();
        printf("%d %d\n", cnt, cnt);
        for (int i = 0; i < cnt; i++) {
            printf("%d %d\n", x[i], y[i]);
        }
    }

    return 0;
}