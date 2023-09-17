#include <iostream>
using namespace std;

constexpr int OFFSET = 14;

constexpr int dx[]{ 1, -1, 0, 0 };
constexpr int dy[]{ 0, 0, 1, -1 };

int N;
int percent[4];
bool visited[OFFSET * 2 + 1][OFFSET * 2 + 1];
double ans;

void dfs(int cnt, int y, int x, double per) {
	if (cnt >= N) {
		ans += per;
		return;
	}

	for (int dir = 0; dir < 4; ++dir) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (visited[ny][nx])
			continue;

		visited[ny][nx] = true;
		dfs(cnt + 1, ny, nx, per * percent[dir] / 100);
		visited[ny][nx] = false;
	}
}

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	cout << fixed;
	cout.precision(10);

	cin >> N;

	for (int dir = 0; dir < 4; ++dir)
		cin >> percent[dir];

	visited[OFFSET][OFFSET] = true;
	dfs(0, OFFSET, OFFSET, 1);
	visited[OFFSET][OFFSET] = false;

	cout << ans << '\n';

	return 0;
}
