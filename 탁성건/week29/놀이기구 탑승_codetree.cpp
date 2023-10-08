#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Pos {
	int y;
	int x;

	bool operator==(const Pos& rhs) const {
		return y == rhs.y && x == rhs.x;
	}

	bool operator<(const Pos& rhs) const {
		if (y < rhs.y)
			return true;
		if (y > rhs.y)
			return false;
		return x < rhs.x;
	}

	static bool isAdj(const Pos& lhs, const Pos& rhs);
};

bool Pos::isAdj(const Pos& lhs, const Pos& rhs) {
	return (abs(rhs.y - lhs.y) + abs(rhs.x - lhs.x)) == 1;
}

struct Student {
	int id;
	vector<int> friends;
};

struct Candidate {
	int friendCnt;
	int emptyCnt;
	Pos pos;

	bool operator<(const Candidate& rhs) const {
		if (friendCnt > rhs.friendCnt)
			return true;
		if (friendCnt < rhs.friendCnt)
			return false;
		if (emptyCnt > rhs.emptyCnt)
			return true;
		if (emptyCnt < rhs.emptyCnt)
			return false;
		return pos < rhs.pos;
	}
};

constexpr int FRIEND_NUM = 4;
constexpr Pos NPOS = { -1, -1 };

constexpr int dx[]{ 1, 0, -1, 0 };
constexpr int dy[]{ 0, -1, 0, 1 };

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N;
	cin >> N;

	const int STUDENT_NUM = N * N;

	vector<Student> students(STUDENT_NUM, { 0, vector<int>(FRIEND_NUM, 0) });
	vector<Pos> studentPos(STUDENT_NUM + 1, NPOS);
	vector<vector<int>> MAP(N, vector<int>(N));

	for (auto& student : students) {
		cin >> student.id;

		for (auto& friendId : student.friends)
			cin >> friendId;
	}

	for (const auto& [id, friends] : students) {
		vector<Candidate> candidates;

		for (int y = 0; y < N; ++y) {
			for (int x = 0; x < N; ++x) {
				if (MAP[y][x])
					continue;
				
				const Pos now = { y, x };
				Candidate candidate = { 0, 0, now };

				for (const auto& friendId : friends)
					if (Pos::isAdj(now, studentPos[friendId]))
						++candidate.friendCnt;

				for (int dir = 0; dir < 4; ++dir) {
					int ny = y + dy[dir];
					int nx = x + dx[dir];

					if (ny < 0 || ny >= N || nx < 0 || nx >= N)
						continue;

					if (!MAP[ny][nx])
						++candidate.emptyCnt;
				}

				candidates.push_back(candidate);
			}
		}

		sort(candidates.begin(), candidates.end());

		const Pos selectedPos = candidates[0].pos;

		MAP[selectedPos.y][selectedPos.x] = id;
		studentPos[id] = selectedPos;
	}

	int score = 0;

	for (const auto& [id, friends] : students) {
		int cnt = 0;
		const Pos& now = studentPos[id];

		for (const auto& friendId : friends)
			if (Pos::isAdj(now, studentPos[friendId]))
				++cnt;

		score += pow(10, cnt - 1);
	}

	cout << score << '\n';

	return 0;
}
