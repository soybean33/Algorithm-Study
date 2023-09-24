#include<iostream>
#include<queue>
#include<unordered_set>
#include<algorithm>
using namespace std;

struct coordi
{
	int y, x;
};

struct Info
{
	int val;
	coordi pt;
	int cnt;
};

int ry[] = { 0, 0, -1, 1 };
int rx[] = { -1, 1, 0, 0 };




int bfs(const int &puzzle_input, const int &zero_index)
{
	int ans = -1;
	unordered_set<int> visited;
	queue<Info> q;

	int puzzle[3][3] = { 0, };

	q.push({ puzzle_input, {zero_index / 3, zero_index % 3}, 0 });
	visited.insert(puzzle_input);

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		if (now.val == 123456780)
		{
			ans = now.cnt;
			break;
		}

		for (int i = 8; i >= 0; i--)
		{
			puzzle[i / 3][i % 3] = now.val % 10;
			now.val /= 10;
		}

		for (int i = 0; i < 4; i++)
		{
			Info next = now;
			
			next.pt.y += ry[i];
			next.pt.x += rx[i];

			if (next.pt.y < 0 || next.pt.y >= 3 ||
				next.pt.x < 0 || next.pt.x >= 3) continue;

			swap(puzzle[now.pt.y][now.pt.x], puzzle[next.pt.y][next.pt.x]);


			next.val = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					next.val *= 10;
					next.val += puzzle[i][j];
				}
			}

			swap(puzzle[now.pt.y][now.pt.x], puzzle[next.pt.y][next.pt.x]);
			if (visited.find(next.val) != visited.end()) continue;
			
			visited.insert(next.val);
			next.cnt++;
			q.push(next);

			
		}

	}

	return ans;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int puzzle_input = 0;
	int zero_index = 0;

	for (int i = 0; i < 9; i++)
	{
		int temp;

		cin >> temp;
		puzzle_input *= 10;
		puzzle_input += temp;

		if (temp == 0)
			zero_index = i;
	}


	cout << bfs(puzzle_input, zero_index);

	return 0;
}