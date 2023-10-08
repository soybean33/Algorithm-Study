#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

constexpr int INF = 1e9;

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N, C;
	cin >> N >> C;

	vector<int> pos(N);

	for (auto& p : pos)
		cin >> p;
	
	sort(pos.begin(), pos.end());

	int left = 0;
	int right = pos[N - 1] - pos[0];
	int res = -1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		int prev = -INF;
		int cnt = 0;

		for (const auto& p : pos) {
			if (p - prev < mid)
				continue;

			prev = p;
			++cnt;
		}

		if (cnt >= C) {
			res = mid;
			left = mid + 1;
		}
		else
			right = mid - 1;
	}

	cout << res << '\n';

	return 0;
}
