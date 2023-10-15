#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
두수를 묶거나 묶지 않을 수 있고 이걸 다 더했을 때 최대값을 구하자

0. 그냥 다 구한 값을 미리 구해놓고 나오는 값들과 비교
1. 1을 제외하고 양수중 큰 값은 다 묶는데 큰 순서대로 묶는다
2. 음수도 다묶는데 음수 끼리만 묶는다.
3. 0이 존재하는 갯수 만큼 남은 음수중 큰수 와 묶는다.

*/


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int N;
	vector<int> zero, positive, negative;
	int zero_index = 0, positive_index = 0, negative_index = 0;

	int ans = 0;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		int temp;

		cin >> temp;

		if (temp == 0)
			zero.push_back(temp);
		else if (temp > 0)
			positive.push_back(temp);
		else
			negative.push_back(temp);
	}

	sort(positive.begin(), positive.end(), greater<int>());
	sort(negative.begin(), negative.end());

	while (positive_index + 1 < positive.size())
	{
		if (positive[positive_index] <= 1 ||
			positive[positive_index + 1] <= 1)
			break;

		ans += positive[positive_index] * positive[positive_index + 1];

		positive_index += 2;
	}

	while (positive_index < positive.size())
	{
		ans += positive[positive_index];
		positive_index++;
	}


	while (negative_index + 1 < negative.size())
	{
		ans += negative[negative_index] * negative[negative_index + 1];
		negative_index += 2;
	}

	if (zero.empty() && negative_index < negative.size())
		ans += negative[negative_index];


	cout << ans;

	return 0;
}