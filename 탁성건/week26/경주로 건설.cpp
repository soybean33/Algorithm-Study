#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

constexpr int INF = 987654321;

constexpr int dx[]{ 1, 0, -1, 0 };
constexpr int dy[]{ 0, -1, 0, 1 };

struct Node {
    int y;
    int x;
    int dir;
    int dist;

    bool operator<(const Node& next) const {
        return dist > next.dist;
    }
};

int solution(vector<vector<int>> board) {
    const int N = board.size();

    priority_queue<Node> pq;
    vector<vector<vector<int>>> minDist(N, vector<vector<int>>(N, vector<int>(4, INF)));

    pq.push({ 0, 0, 0, 0 });
    pq.push({ 0, 0, 3, 0 });

    minDist[0][0][0] = 0;
    minDist[0][0][3] = 0;

    while (!pq.empty()) {
        auto [y, x, dir, dist] = pq.top();
        pq.pop();

        minDist[y][x][dir];

        if (minDist[y][x][dir] < dist)
            continue;

        for (int ndir = 0; ndir < 4; ndir++) {
            int ny = y + dy[ndir];
            int nx = x + dx[ndir];
            int ndist = dist;

            if (ny < 0 || ny >= N || nx < 0 || nx >= N || board[ny][nx] == 1)
                continue;

            (dir + ndir) % 2 == 0 ? ndist += 100 : ndist += 600;

            if (minDist[ny][nx][ndir] <= ndist)
                continue;

            minDist[ny][nx][ndir] = ndist;
            pq.push({ ny, nx, ndir, ndist });
        }
    }

    return min({ minDist[N - 1][N - 1][0], minDist[N - 1][N - 1][1], minDist[N - 1][N - 1][2], minDist[N - 1][N - 1][3] });
}
