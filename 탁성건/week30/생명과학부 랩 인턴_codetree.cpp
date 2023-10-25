#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 100;
constexpr int MAX_M = 100;
constexpr int dx[]{ 1, 0, -1, 0 };  // R, U, L, D
constexpr int dy[]{ 0, -1, 0, 1 };
constexpr int input2dir[]{ 0, 1, 3, 0, 2 };

struct Mold {
	int y;
	int x;
	int speed;
	int dir;
	int sz;

	bool operator<(const Mold& rhs) const {
		return sz > rhs.sz;
	}
};

int N, M, K;
int MAP[MAX_N + 1][MAX_M + 1];
Mold molds[MAX_N * MAX_M + 1];

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	cin >> N >> M >> K;

	for (int id = 1; id <= K; ++id) {
		auto& [y, x, speed, dir, sz] = molds[id];
		cin >> y >> x >> speed >> dir >> sz;
		dir = input2dir[dir];
		dir % 2 ? speed %= (2 * N - 2) : speed %= (2 * M - 2);
	}

	sort(molds + 1, molds + K + 1);

	for (int id = 1; id <= K; ++id) {
		auto& [y, x, speed, dir, sz] = molds[id];
		MAP[y][x] = id;
	}

	int ans = 0;

	for (int sx = 1; sx <= M; ++sx) {
		// 채집
		for (int sy = 1; sy <= N; ++sy) {
			if (!MAP[sy][sx])
				continue;

			int& sz = molds[MAP[sy][sx]].sz;

			ans += sz;
			sz = 0;

			MAP[sy][sx] = 0;

			break;
		}

		// 곰팡이 이동
		for (int id = 1; id <= K; ++id) {
			auto& [y, x, speed, dir, sz] = molds[id];

			if (!sz) continue;

			if (MAP[y][x] == id)
				MAP[y][x] = 0;

			for (int i = 0; i < speed; ++i) {
				y += dy[dir];
				x += dx[dir];

				if (y <= 0 || y > N || x <= 0 || x > M) {
					dir = (dir + 2) % 4;
					y += dy[dir] * 2;
					x += dx[dir] * 2;
				}
			}

			if (MAP[y][x] != 0 && MAP[y][x] < id) {
				sz = 0;
				continue;
			}

			MAP[y][x] = id;
		}
	}

	cout << ans << '\n';

	return 0;
}
