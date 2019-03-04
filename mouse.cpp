#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "grader.h"
using namespace std;

typedef pair<int,int> ii;

#define fi first
#define se second

const int MAXN = 300;

int query(vector<int> v);

vector<int> get_derangement(int n) {
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		v[i] = i + 1;

	while (true) {
		random_shuffle(v.begin(), v.end());
		int cnt = query(v);
		if (cnt == n) 
			return vector<int>();
		if (cnt == 0)
			return v;
	}
}

vector<ii> tournament[MAXN];

void fill(int k, const vector<int>& table) {
	int n = table.size();
	for (int i = 0; i < n / 2; i++) 
		tournament[k].push_back(ii(table[i], table[n-1-i]));
}

int round_robin(int n) {
	vector<int> table(n);
	for (int i = 0; i < n; i++)
		table[i] = i;
	fill(0, table);

	for (int i = 1; i + 1 < n; i++) {
		int tmp = table[n-1];
		for (int j = n-1; j > 1; j--) 
			table[j] = table[j-1];
		table[1] = tmp;

		fill(i, table);
	}

	return n - 1;
}

bool can_swap(ii p, int n) {
	return p.fi < n && p.se < n;
}

vector<int> do_swap(const vector<int>& v, const vector<ii>& tournament, int lo, int hi) {
	vector<int> res = v;
	for (int i = lo; i < hi; i++) {
		ii p = tournament[i];
		
		if (!can_swap(p, v.size()))
			continue;

		swap(res[p.first], res[p.second]);
	}

	return res;
}

vector<ii> useful_swaps;

void find_pairs(const vector<int>& v, const vector<ii>& tournament, int lo, int hi, int cnt) {
	if (lo >= hi || cnt == 0)
		return;

	if (lo + 1 == hi) {
		useful_swaps.push_back(tournament[lo]);
		return;
	}

	int mid = (lo + hi) / 2;

	vector<int> v_l = do_swap(v, tournament, lo, mid);
	int cnt_l = query(v_l);
	int cnt_r = cnt - cnt_l;

	find_pairs(v, tournament, lo, mid, cnt_l);
	find_pairs(v, tournament, mid, hi, cnt_r);
}

vector<int> adjList[MAXN];
bool visited[MAXN];

vector<ii> find_swap_cycle(int i) {
	int root = i;

	int par = i; visited[par] = true;
	int cur = adjList[i][0]; visited[cur] = true;

	vector<ii> res;
	res.push_back(ii(par, cur));
	
	while (true) {
		int nxt = (adjList[cur][0] != par ? adjList[cur][0] : adjList[cur][1]);
		visited[nxt] = true;

		if (nxt == root)
			break;

		res.push_back(ii(cur, nxt));

		par = cur;
		cur = nxt;
	}

	return res;
}

void solve(int N) {

	int n = N + N % 2; // make even

	vector<int> v = get_derangement(N);

	if (v.empty())
		return;

	int turns = round_robin(n);

	for (int i = 0; i < turns; i++) {
		vector<int> w = do_swap(v, tournament[i], 0, n / 2);
		int cnt = query(w);

		if (cnt == N)
			return;

		find_pairs(v, tournament[i], 0, n / 2, cnt);
	}

	// construct graph
	for (ii p : useful_swaps) {
		adjList[p.fi].push_back(p.se);
		adjList[p.se].push_back(p.fi);
	}

	vector<ii> working_swaps;

	for (int i = 0; i < N; i++) {
		if (visited[i])
			continue;

		if (adjList[i].size() == 1) {
			if (i < adjList[i][0])
				working_swaps.push_back(ii(i, adjList[i][0]));
			continue;
		}

		vector<ii> cycle = find_swap_cycle(i);

		vector<int> tmp = do_swap(v, cycle, 0, cycle.size());
		int cnt = query(tmp);
		if (cnt == N)
			return;

		if (cnt == 0)
			reverse(cycle.begin(), cycle.end());

		for (ii p : cycle) {
			working_swaps.push_back(p);
		}
	}

	vector<int> final = do_swap(v, working_swaps, 0, working_swaps.size());
	query(final);
}

