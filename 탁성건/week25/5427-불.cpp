#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pii = pair<int, int>;

enum {
	EMPTY = '.',
	WALL = '#',
	PERSON = '@',
	FIRE = '*',
	EXIT = '&'
};

const int dx[]{ 1, 0, -1, 0 };
const int dy[]{ 0, -1, 0, 1 };

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int T;
	cin >> T;

	while (T--) {
		int W, H;
		cin >> W >> H;

		vector<vector<char>> MAP(H + 2, vector<char>(W + 2));
		queue<pii> fire;
		queue<pii> person;

		for (int y = 0; y <= H + 1; ++y)
			MAP[y][0] = MAP[y][W + 1] = EXIT;

		for (int x = 0; x <= W + 1; ++x)
			MAP[0][x] = MAP[H + 1][x] = EXIT;

		for (int y = 1; y <= H; ++y) {
			for (int x = 1; x <= W; ++x) {
				cin >> MAP[y][x];

				if (MAP[y][x] == FIRE)
					fire.push({ y, x });
				else if (MAP[y][x] == PERSON)
					person.push({ y, x });
			}
		}

		int ans = -1;
		int cnt = 0;

		while (!fire.empty() || !person.empty()) {
			++cnt;

			int sz = fire.size();

			while (sz--) {
				auto [y, x] = fire.front();
				fire.pop();

				for (int dir = 0; dir < 4; ++dir) {
					int ny = y + dy[dir];
					int nx = x + dx[dir];

					if (MAP[ny][nx] == WALL || MAP[ny][nx] == FIRE || MAP[ny][nx] == EXIT)
						continue;

					MAP[ny][nx] = FIRE;
					fire.push({ ny, nx });
				}
			}

			sz = person.size();

			while (sz--) {
				auto [y, x] = person.front();
				person.pop();

				for (int dir = 0; dir < 4; ++dir) {
					int ny = y + dy[dir];
					int nx = x + dx[dir];

					if (MAP[ny][nx] == WALL || MAP[ny][nx] == FIRE || MAP[ny][nx] == PERSON)
						continue;

					if (MAP[ny][nx] == EXIT) {
						ans = cnt;
						sz = 0;
						queue<pii>().swap(fire);
						queue<pii>().swap(person);
						break;
					}

					MAP[ny][nx] = PERSON;
					person.push({ ny, nx });
				}
			}
		}

		if (ans == -1)
			cout << "IMPOSSIBLE\n";
		else
			cout << ans << '\n';
	}

	return 0;
}
