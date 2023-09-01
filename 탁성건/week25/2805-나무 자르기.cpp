#include <iostream>
#include <vector>
using namespace std;

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N, M;
	cin >> N >> M;

	vector<int> height(N);

	int maxH = 0;

	for (int& h : height) {
		cin >> h;
		maxH = maxH > h ? maxH : h;
	}

	int left = 0;
	int right = maxH;
	int ans = 0;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		long long len = 0;

		for (const int& h : height)
			if (h > mid)
				len += h - mid;

		if (len >= M) {
			left = mid + 1;
			ans = mid;
		}
		else {
			right = mid - 1;
		}
	}

	cout << ans << '\n';

	return 0;
}
