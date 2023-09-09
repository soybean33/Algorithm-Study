#include<iostream>
#include<string>
using namespace std;

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int N, M, maxnum = -1;
	int rect[6][6];
	
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < M; j++)
			rect[i][j] = (int)(str[j] - '0');
	}


	for (int i = 0; i < (1 << (N * M)); i++)
	{
		int sum = 0;
		int cur = 0;
		for (int j = 0; j < N; j++)
		{
			cur = 0;
			for (int k = 0; k < M; k++)
			{
				int m = j * M + k;
				if ((i & (1 << m)) == 0)
					cur = cur * 10 + rect[j][k];
				else
				{
					sum += cur;
					cur = 0;
				}
			}
			sum += cur;
		}

		for (int j = 0; j < M; j++)
		{
			cur = 0;
			for (int k = 0; k < N; k++)
			{
				int m = k * M + j;
				if ((i & (1 << m)) != 0)
					cur = cur * 10 + rect[k][j];
				else
				{
					sum += cur;
					cur = 0;
				}
			}
			sum += cur;
		}
		maxnum = max(maxnum, sum);
	}

	cout << maxnum;
}