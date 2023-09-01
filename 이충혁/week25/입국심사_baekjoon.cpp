#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


int N, M;
vector<long long> j_table;


// parameter search
long long solve_func()
{
	long long ans = 0;

	long long left = 0;
	long long right = j_table[0] * M;
	long long mid;

	while (left <= right)
	{
		long long cnt = 0;
		mid = (left + right) / 2;

		for (auto &val : j_table)
		{
			cnt += mid / val;
		}

		if (cnt >= M)
		{
			right = mid - 1;

			ans = mid;
		}
		else
		{
			left = mid + 1;
		}

	}


	return ans;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	cin >> N >> M;
	j_table.resize(N);

	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		j_table[i] = temp;
	}

	sort(j_table.begin(), j_table.end());
	cout << solve_func();

	return 0;
}