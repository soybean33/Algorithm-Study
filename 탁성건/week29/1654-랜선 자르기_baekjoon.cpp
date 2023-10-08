#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int K, N;
	cin >> K >> N;

	vector<int> cables(K);

	ll left = 1;
	ll right = 1;
	ll ans = 1;

	for (int& cable : cables) {
		cin >> cable;
		right = right > cable ? right : cable;
	}

	while (left <= right) {
		ll mid = left + (right - left) / 2;
		ll cnt = 0;

		for (const int& cable : cables)
			cnt += cable / mid;

		if (cnt >= N) {
			ans = mid;
			left = mid + 1;
		}
		else
			right = mid - 1;
	}

	cout << ans << '\n';

	return 0;
}
