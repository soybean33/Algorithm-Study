#include<iostream>
#include<cstring>
using namespace std;

const int HOUSE_SIZE = 50;
const int DIR_SIZE = 3;

enum {
	HORIZONTAL = 0,
	VERTICAL = 1,
	DIAGONAL = 2
};

int MAP[HOUSE_SIZE][HOUSE_SIZE] = { 0, };
long long DP[HOUSE_SIZE][HOUSE_SIZE][DIR_SIZE];


int input_func(const int& N)
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> MAP[i][j];
		}
	}

	return 0;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int N; // 집의 크기

	cin >> N;

	memset(MAP, -1, sizeof(MAP));
	input_func(N);

	DP[1][2][HORIZONTAL] = 1;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (i == 1 && j == 1) continue;
			if (MAP[i][j] == 1) continue;

			if (MAP[i][j + 1] != 1)
				DP[i][j + 1][HORIZONTAL] = DP[i][j][DIAGONAL] + DP[i][j][HORIZONTAL];
			if (MAP[i + 1][j] != 1)
				DP[i + 1][j][VERTICAL] = DP[i][j][DIAGONAL] + DP[i][j][VERTICAL];
			if (i + 1 <= N && j + 1 <= N)
			{
				if (MAP[i + 1][j] == 0 && MAP[i][j + 1] == 0 && MAP[i + 1][j + 1] == 0)
					DP[i + 1][j + 1][2] = DP[i][j][0] + DP[i][j][1] + DP[i][j][2];


			}
		}
	}

	cout << DP[N][N][HORIZONTAL] + DP[N][N][VERTICAL] + DP[N][N][DIAGONAL] << "\n";

	return 0;
}