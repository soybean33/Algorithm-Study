#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 1000000

long long N, M;
int tree[MAX];

// 이분 탐색
// cut이 long 넘을 수 있다 조심하자
int solve_func()
{
	int start = 0;
	int end = 20e8;
	int mid;
	int ans = 0;;
	while (start <= end)
	{
		long long cut = 0;
		mid = start + (end - start) / 2;

		for (int i = N - 1; i >= 0; i--)
		{
			if (tree[i] < mid)
				break;

			cut += tree[i] - mid;
		}

		if (cut >= M)
		{
			start = mid + 1;
			ans = mid;
		}
		else
		{
			end = mid - 1;
		}
	}

	return ans;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		cin >> tree[i];
	}
	sort(tree, tree + N);

	cout << solve_func();

	return 0;
}