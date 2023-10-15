#include <iostream>
using namespace std;

constexpr int MAX_N = 300;
constexpr int MAX_M = 300;

constexpr int dy[]{ 0, 1, 0, -1 };
constexpr int dx[]{ 1, 0, -1, 0 };

int MAP[MAX_N][MAX_M];

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N, M, R;
	cin >> N >> M >> R;

	for (int y = 0; y < N; ++y)
		for (int x = 0; x < M; ++x)
			cin >> MAP[y][x];

	int n = N;
	int m = M;
	int offset = 0;

	while (true) {
		if (n == 0 || m == 0)
			break;

		int sz = n * m - (n - 2) * (m - 2);
		int r = R % sz;
		
		while (r--) {
			int y = offset;
			int x = offset;
			int dir = 0;
			int temp = MAP[y][x];

			while (dir < 4) {
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				if (ny < offset || ny >= offset + n || nx < offset || nx >= offset + m) {
					++dir;
					continue;
				}

				MAP[y][x] = MAP[ny][nx];
				y = ny;
				x = nx;
			}

			MAP[y + 1][x] = temp;
		}

		n -= 2;
		m -= 2;
		++offset;
	}

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x)
			cout << MAP[y][x] << ' ';
		cout << '\n';
	}

	return 0;
}
