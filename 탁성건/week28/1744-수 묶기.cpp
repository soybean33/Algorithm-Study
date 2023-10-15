#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N;
	cin >> N;

	vector<int> one;
	vector<int> pos;
	vector<int> neg;
	vector<int> zero;

	for (int i = 0; i < N; ++i) {
		int num;
		cin >> num;
		
		if (num == 1)
			one.emplace_back(num);
		else if (num > 0)
			pos.emplace_back(num);
		else if (num < 0)
			neg.emplace_back(num);
		else
			zero.emplace_back(num);
	}

	sort(pos.begin(), pos.end(), greater<int>());
	sort(neg.begin(), neg.end());

	int ans = one.size();

	for (int i = 0; i < pos.size() - (pos.size() % 2); i += 2)
		ans += pos[i] * pos[i + 1];

	for (int i = 0; i < neg.size() - (neg.size() % 2); i += 2)
		ans += neg[i] * neg[i + 1];

	if (pos.size() % 2)
		ans += pos[pos.size() - 1];

	if (neg.size() % 2 && zero.empty())
		ans += neg[neg.size() - 1];

	cout << ans << '\n';

	return 0;
}
