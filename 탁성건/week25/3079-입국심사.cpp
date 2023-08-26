#include <iostream>
#include <vector>
using namespace std;

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N, M;
	cin >> N >> M;

	vector<int> T(N);

	int maxT = 0;

	for (int& t : T) {
		cin >> t;
		maxT = maxT > t ? maxT : t;
	}

	long long left = 1;
	long long right = (long long)M * maxT;
	long long ans = 1;

	while (left <= right) {
		long long mid = left + (right - left) / 2;
		long long cnt = 0;

		for (const int& t : T) {
			cnt += mid / t;
			if (cnt >= M)
				break;
		}

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
