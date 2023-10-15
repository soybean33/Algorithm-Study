#include <iostream>
using namespace std;

constexpr int MAX_N = 10;

int dp[MAX_N + 1];

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;

	for (int i = 3; i <= MAX_N; ++i)
		dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

	int T;
	cin >> T;

	while (T--) {
		int n;
		cin >> n;
		cout << dp[n] << '\n';
	}

	return 0;
}
