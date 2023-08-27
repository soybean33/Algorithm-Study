#include<iostream>
#include<string>
#include<cstring>
#include<queue>
using namespace std;

struct coordi
{
	int y, x;
};

struct Q_INFO
{
	coordi pt;
	int who; // 0 : 상근, 1 : 불
	int cnt;
};

const int MAP_SIZE = 1010;

const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

enum MAP_VAL {
	EXIT = -1,
	EMPTY = 0,
	WALL = 1,
	VISITED = 2,
	FIRE = 3
};

int w, h;
int MAP[MAP_SIZE][MAP_SIZE];
coordi st;
queue<Q_INFO> q;

int input_func()
{
	string str;

	memset(MAP, EXIT, sizeof(MAP));
	q = queue<Q_INFO>();
	
	for (int i = 0; i < h; i++)
	{
		cin >> str;

		for (int j = 0; j < w; j++)
		{
			switch (str[j])
			{
			case '.':
				MAP[i + 1][j + 1] = EMPTY;
				break;
			case '#':
				MAP[i + 1][j + 1] = WALL;
				break;
			case '@':
				MAP[i + 1][j + 1] = VISITED;
				st = { i + 1, j + 1 };
				break;
			case '*':
				MAP[i + 1][j + 1] = FIRE;
				q.push({ {i + 1, j + 1}, 1, 0});
				break;
			default:
				cout << "ERROR!!\n";
			}
		}
	}
	
	return 0;
}

// bfs
int solve_func()
{
	q.push({ st, 0, 0 });

	while (!q.empty())
	{
		Q_INFO now = q.front();
		q.pop();


		for (int i = 0; i < 4; i++)
		{
			coordi next = now.pt;
			next.y += ry[i];
			next.x += rx[i];

			if (now.who == 1) // 불일 때
			{
				if (MAP[next.y][next.x] == WALL ||
					MAP[next.y][next.x] == EXIT ||
					MAP[next.y][next.x] == FIRE) continue;
				MAP[next.y][next.x] = FIRE;
			}
			else
			{
				if(MAP[next.y][next.x] == EXIT)
					return now.cnt + 1;

				if (MAP[next.y][next.x] != EMPTY) continue;

				MAP[next.y][next.x] = VISITED;
			}

			q.push({ next, now.who, now.cnt + 1 });
		}
	}

	return -1;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	int T;

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> w >> h;
		input_func();

		int ans = solve_func();
		if (ans == -1)
			cout << "IMPOSSIBLE\n";
		else
			cout << ans << "\n";
	}



	return 0;
}