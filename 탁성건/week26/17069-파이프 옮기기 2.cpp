#include <iostream>
#include <cmath>
using namespace std;

constexpr int MAX_N = 32;
constexpr int dx[]{ 1, 1, 0 };  // R, RD, D
constexpr int dy[]{ 0, 1, 1 };

int N;
int MAP[MAX_N + 1][MAX_N + 1];
long long dp[MAX_N + 1][MAX_N + 1][3];

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	cin >> N;

	for (int y = 0; y < N; ++y)
		for (int x = 0; x < N; ++x)
			cin >> MAP[y][x];

	dp[0][1][0] = 1;

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			for (int dir = 0; dir < 3; ++dir) {
				for (int ndir = 0; ndir < 3; ++ndir) {
					if (abs(dir - ndir) == 2)
						continue;

					int ny = y + dy[ndir];
					int nx = x + dx[ndir];

					if (MAP[ny][nx])
						continue;

					if (ndir == 1 && (MAP[y][nx] || MAP[ny][x]))
						continue;

					dp[ny][nx][ndir] += dp[y][x][dir];
				}
			}
		}
	}

	long long ans = 0;

	for (int dir = 0; dir < 3; ++dir)
		ans += dp[N - 1][N - 1][dir];

	cout << ans << '\n';

	return 0;
}
