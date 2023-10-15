#include <iostream>
#include <vector>
using namespace std;

int N, K;

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	cin >> N >> K;
	
	vector<int> coins(N);

	for (int& coin : coins)
		cin >> coin;

	int ans = 0;

	for (int i = N - 1; i >= 0; --i) {
		ans += K / coins[i];
		K %= coins[i];
	}

	cout << ans << '\n';

	return 0;
}
