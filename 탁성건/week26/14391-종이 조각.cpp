#include <iostream>
using namespace std;

constexpr int MAX_N = 4;
constexpr int MAX_M = 4;

int N, M;
int MAP[MAX_N][MAX_M];
int maxTotalSum;

void dfs(int y, int x, int state, int totalSum) {
	if (x >= M) {
		++y;
		x = 0;
	}
	
	if (y >= N) {
		maxTotalSum = maxTotalSum > totalSum ? maxTotalSum : totalSum;
		return;
	}

	if (state & (1 << (y * M + x))) {
		dfs(y, x + 1, state, totalSum);
		return;
	}

	int sum = 0;
	int nstate = state;

	for (int ny = y; ny < N; ++ny) {
		if (nstate & (1 << (ny * M + x)))
			break;
		nstate |= (1 << (ny * M + x));
		sum = sum * 10 + MAP[ny][x];
		dfs(y, x + 1, nstate, totalSum + sum);
	}

	sum = 0;
	nstate = state;

	for (int nx = x; nx < M; ++nx) {
		if (nstate & (1 << (y * M + nx)))
			break;
		nstate |= (1 << (y * M + nx));
		sum = sum * 10 + MAP[y][nx];
		dfs(y, nx, nstate, totalSum + sum);
	}
}

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	cin >> N >> M;
	
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			char ch;
			cin >> ch;
			MAP[y][x] = ch - '0';
		}
	}

	dfs(0, 0, 0, 0);

	cout << maxTotalSum << '\n';

	return 0;
}
