#include <iostream>
#include <vector>

int Solution(const int& N, std::vector<int>& DP) {

	if(N == 1) {return 1;}	// 1을 만들 수 있는 방법의 수 1 -> 1
	if(N == 2) {return 2;}	// 2를 만들 수 있는 방법의 수 2 -> 1 + 1, 2
	if(N == 3) {return 4;}	// 3을 만들 수 있는 방법의 수 4 -> 1 + 1 + 1, 1 + 2, 2 + 1, 3 

	if(DP[N] != -1) {return DP[N];}	// 이미 기록된 값이 있다면 그 값을 return

	return DP[N] = Solution(N-1, DP) + Solution(N-2, DP) + Solution(N-3, DP);	// 가지 수 계산
}

void Input(int& N) {

	std::cin >> N;

	return;
}

int main() {

	int T;	// T: 테스트 케이스의 수
	std::cin >> T;

	for(int tc=0; tc<T; ++tc) {
		int N;	// N: 정수 N
		std::vector<int> DP;	// DP[i]: i를 만들수 있는 방법의 수

		Input(N);

		DP.assign(N + 1, -1);	// -1로 초기화

		std::cout << Solution(N, DP) << '\n';
	}

	return 0;
}