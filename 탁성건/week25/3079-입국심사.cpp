#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 21e8;

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N, M;
	cin >> N >> M;

	vector<int> T(N);

	int minT = INF;

	for (int& t : T) {
		cin >> t;
		minT = minT < t ? minT : t;
	}

	long long left = 1;
	long long right = static_cast<long long>(M) * minT;
	long long ans = right;

	while (left <= right) {
		long long mid = left + (right - left) / 2;
		long long cnt = 0;

		for (const int& t : T)
			cnt += mid / t;

		if (cnt >= M) {
			ans = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	cout << ans << '\n';

	return 0;
}
