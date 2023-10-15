#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int N, K;
	int ans = 0;
	vector<int> val;

	cin >> N >> K;
	val.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> val[i];
	}

	for (int i = N - 1; i >= 0; i--)
	{
		int temp;
		temp = K / val[i];
		K = K - val[i] * temp;
		ans += temp;
	}

	cout << ans;

	return 0;
}