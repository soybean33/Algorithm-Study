#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
using namespace std;

const vector<int> changeIdx[9] = {
	{1, 3},
	{0, 2, 4},
	{1, 5},
	{0, 4, 6},
	{1, 3, 5, 7},
	{2, 4, 8},
	{3, 7},
	{4, 6, 8},
	{5, 7},
};

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	string st(9, '0');
	const string en = "123456780";

	for (char& ch : st)
		cin >> ch;

	int cnt = 0;
	queue<string> q;
	unordered_set<string> visited;

	q.push(st);
	visited.insert(st);

	while (!q.empty()) {
		int sz = q.size();

		while (sz--) {
			string now = q.front();
			q.pop();

			if (now == en) {
				cout << cnt << '\n';
				return 0;
			}

			for (int i = 0; i < 9; ++i) {
				if (now[i] != '0')
					continue;

				for (int j : changeIdx[i]) {
					string next = now;
					swap(next[i], next[j]);

					if (visited.find(next) != visited.end())
						continue;

					q.push(next);
					visited.insert(next);
				}
			}
		}

		++cnt;
	}

	cout << "-1\n";

	return 0;
}
