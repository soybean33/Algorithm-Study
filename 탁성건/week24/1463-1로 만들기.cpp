#include <iostream>
#include <vector>
using namespace std;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  cin >> N;

  vector<int> dp(N + 1);

  for (int i = 2; i <= N; ++i) {
    dp[i] = dp[i - 1] + 1;

    if (i % 2 == 0 && dp[i] > dp[i / 2] + 1)
      dp[i] = dp[i / 2] + 1;

    if (i % 3 == 0 && dp[i] > dp[i / 3] + 1)
      dp[i] = dp[i / 3] + 1;
  }

  cout << dp[N] << '\n';

  return 0;
}
