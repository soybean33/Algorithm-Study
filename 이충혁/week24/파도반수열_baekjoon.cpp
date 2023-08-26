#include <iostream>
using namespace std;

using ll = long long;

const int TRI_SIZE = 111;

int T;
int N;
ll triangle[TRI_SIZE];

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int cycle = 6;

	triangle[1] = 1;
	triangle[2] = 1;
	triangle[3] = 1;
	triangle[4] = 2;
	triangle[5] = 2;

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N;

		for (cycle; cycle <= N; cycle++)
		{
			triangle[cycle] = triangle[cycle - 1] + triangle[cycle - 5];
		}

		cout << triangle[N] << "\n";
	}

	return 0;
}