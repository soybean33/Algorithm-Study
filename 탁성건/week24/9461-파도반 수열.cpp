#include <iostream>
using namespace std;

constexpr int MAX_N = 100;

long long dp[MAX_N + 1] = {0, 1, 1, 1, 2, 2, 3, 4, 5, 7, 9};

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  for (int i = 11; i <= MAX_N; ++i)
    dp[i] = dp[i - 1] + dp[i - 5];

  int T;
  cin >> T;

  while (T--) {
    int n;
    cin >> n;
    cout << dp[n] << '\n';
  }

  return 0;
}
