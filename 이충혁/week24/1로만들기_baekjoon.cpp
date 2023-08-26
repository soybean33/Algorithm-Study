#include <iostream>
#include <algorithm>
using namespace std;

const int DP_SIZE = 1010101;

int N;
int dp[DP_SIZE];


int main()
{
	cin.tie(nullptr)->sync_with_stdio(false);

	cin >> N;

	dp[1] = 0;
	dp[2] = 1;
	dp[3] = 1;

	for (int i = 4; i <= N; i++)
	{
		if (i % 6 == 0)
		{
			dp[i] = 1 + min(min(dp[i - 1], dp[i / 2]), dp[i / 3]);
		}
		else if (i % 3 == 0)
		{
			dp[i] = 1 + min(dp[i - 1], dp[i / 3]);
		}
		else if (i % 2 == 0)
		{
			dp[i] = 1 + min(dp[i - 1], dp[i / 2]);
		}
		else
		{
			dp[i] = 1 + dp[i - 1];
		}

	}

	cout << dp[N] << "\n";

	return 0;
}