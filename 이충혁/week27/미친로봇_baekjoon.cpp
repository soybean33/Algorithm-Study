#include<iostream>
#include<vector>
using namespace std;

struct coordi {
	int y, x;
};

const int MAP_MAX = 40;
const int ry[] = { 1, -1, 0, 0 };
const int rx[] = { 0, 0, 1, -1 };

int visited[MAP_MAX][MAP_MAX] = { 0, };

double dfs(coordi pt, int cnt, const int &N, const vector<double> &percent)
{
	double ret = 0.0;

	if (cnt == N) return 1.0;

	visited[pt.y][pt.x] = true;

	for (int i = 0; i < 4; i++)
	{
		coordi next = pt;

		next.y += ry[i];
		next.x += rx[i];


		if (visited[next.y][next.x] == true) continue;

		ret = ret + percent[i] * dfs(next, cnt + 1, N, percent);
	}

	visited[pt.y][pt.x] = false;
	return ret;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int N;
	vector<double>percent;

	cin >> N;

	for (int i = 0; i < 4; i++)
	{
		int temp;
		cin >> temp;
		percent.push_back(temp / 100.0);
	}

	// 출력 형식을 잘 확인하자
	cout.precision(10);
	cout << fixed << dfs({ 20, 20 }, 0, N, percent) << "\n";
	return 0;
}