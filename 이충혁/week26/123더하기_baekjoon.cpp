#include <iostream>
using namespace std;

const int DP_SIZE = 100;
int dp[DP_SIZE];

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	// init
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 4;

	for (int i = 4; i < DP_SIZE; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
	}

	int T, N;

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N;

		cout << dp[N] << "\n";
	}

	return 0;
}