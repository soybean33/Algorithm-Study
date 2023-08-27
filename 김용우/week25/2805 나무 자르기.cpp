#include <iostream>
#include <vector>
#include <algorithm>

int Solution(const int& n, const int& m, const std::vector<int>& height, const int& maxHeight) {

	int answer = 0;	// answer: 절단기에 설정할 수 있는 높이의 최댓값

	int lowHeight = 0, highHeight = maxHeight;	// lowHeight: 모든 나무 다 자른 경우, highHeight: 가장 큰 나무 보다 너 많이 자를 필요 없음	

	while(lowHeight <= highHeight) {
		int midHeight = (lowHeight + highHeight) / 2;	// midHeight: 자르기를 시도해 볼 전단기의 높이

		long long possibleHeight = 0;	// possibleHeight: 상근이가 집으로 가져갈 수 있는 나무의 높이
		for(const int& treeHeight : height) {
			int tmpHeight = treeHeight - midHeight;	// tmpHeight: 현재 나무에서 가져갈 수 있는 나무의 높이
			if (tmpHeight > 0) {possibleHeight += tmpHeight;}	// 0보다 큰 경우만 가져감
		}

		if(possibleHeight < m) {highHeight = midHeight - 1;}	// 나무를 더 많이 잘라야함
		else if(possibleHeight >= m) {	// 나무를 충분히 잘랐음
			lowHeight = midHeight + 1;
			answer = midHeight;
		}
	}

	return answer;
}

void Input(int& n, int& m, std::vector<int>& height, int& maxHeight) {

	std::cin >> n >> m;

	height.assign(n, 0);

	for(int i=0; i<n; ++i) {
		std::cin >> height[i];
		maxHeight = std::max(maxHeight, height[i]);	// 가장 큰 나무의 높이 값 갱신
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;	// n: 나무의 수, m: 상근이가 집으로 가져가려고 하는 나무의 길이
	std::vector<int> height;	// height[i]: i 번째 남의 높이
	int maxHeight = 0;	// maxHeight: 가장 큰 나무의 높이

	Input(n, m, height, maxHeight);

	std::cout << Solution(n, m, height, maxHeight);

	return 0;
}