#include <string>
#include <vector>
#include <unordered_map>

std::vector<int> solution(std::vector<std::string> gems) {
    std::vector<int> answer(2);	// answer[0]: 시작 진열대 번호, answer[1]: 끝 진열대 번호

	std::unordered_map<std::string, int> gemUm;	// gemUm["보석"]: 진열대의 "보석"의 개수
	int gemTypeCnt = 0;	// gemTypeCnt: 서로 다른 보석의 개수 -> 보석 종류의 수

	for(const std::string& gem : gems) {	// gem: 보석 이름
        if(gemUm.find(gem) != gemUm.end()) {continue;}	// 이미 hash에 포함되었다면 continue
		
        gemUm.insert({gem, 0});	// hash에 추가
        ++gemTypeCnt;	// 보석의 종류 증가
	}

	int left = 0, right = 0;	// left: 투포인터 왼쪽, right: 투 포인터 오른쪽
	int len = gems.size() + 2;	// len: 구간의 길이
	int cnt = 0;	// cnt: 보석 종류의 개수

	// 투포인터 초기 세팅
	for(int i=0; i<gemTypeCnt-1; ++i) {
		std::string gem = gems[i];	// gem: 보석 이름
		if(gemUm[gem] == 0) {++cnt;}	// 새로운 종류의 보석이라면 ++cnt
		++gemUm[gem];
		++right;
	}

	--right;

	int gemsSize = gems.size();	// gemsSize: 총 보석들의 개수
	while(right < gemsSize) {
		if(cnt == gemTypeCnt) {	// 보든 종류의 보석이 등장했다면 -> ++left
			int currLen = right - left + 1;	// currLen: 구간의 길이

			if(currLen < len) {	// 더 짧은 구간을 발견 했다면
				answer[0] = left + 1;
				answer[1] = right + 1;
				len = currLen;

				if(len == gemTypeCnt) {break;}	// 구간이 최소 길이라면 break
			}

			std::string gem = gems[left];	// gem: 진열대에서 빠질 보석 이름
			if(gemUm[gem] == 1) {--cnt;}	// 1개만 있는 보석일 경우 보석 종류 감소
			--gemUm[gem];
			++left;
		}
		else {	// 모든 종류의 보석이 등장하지 않았다면 -> ++right
			++right;
            if(right >= gemsSize) {break;}	// 범위 벗어나면 break
            
			std::string gem = gems[right];	// gem: 진열대에 추가될 보석 이름
			if(gemUm[gem] == 0) {++cnt;}	// 새로운 종류의 보석이라면 ++cnt
			++gemUm[gem];
		}		
	}
    
    return answer;
}