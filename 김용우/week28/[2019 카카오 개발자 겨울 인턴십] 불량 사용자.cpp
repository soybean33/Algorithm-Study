#include <string>
#include <vector>
#include <set>

void Dfs(int depth, const std::vector<std::string>& user_id, const std::vector<std::string>& banned_id, const int& userIdNum, const int& bannedIdNum, std::vector<bool>& visited, std::set<std::string>& s) {

	if(depth == bannedIdNum) {  // 모든 불량 사용자 아이디에 대하여 매칭을 완료한 경우
		std::string tmp = "";   // tmp: 사용자가 불량 사용자 인것에 대하여 문자열로 나타냄
		for(const bool chk : visited) {
			tmp += chk ? 1 : 0; // 불량 사용자라면 1의 값, 아니라면 0의 값
		}
		s.insert(tmp);  // 중복을 제거하기 위하여 집합에 넣음

		return;
	}

	for(int i=0; i<userIdNum; ++i) {
		if(visited[i]) {continue;}  // 이미 i 번째 응모자 아이디가 불량 사용자라면 continue
		if(banned_id[depth].length() != user_id[i].length()) {continue;}    // i 번째 응모자 아이디와 불량 사용자의 아이디의 길이가 다르면 후보가 될 수 없으므로 continue
		
		int idLen = banned_id[depth].length();  // idLen: 불량 사용자의 아이디 길이
		bool flag = true;   // flag: 불량 사용자가 될 수 있으면 true

		for(int j=0; j<idLen; ++j) {
			if(banned_id[depth][j] == '*') {continue;}  // * 표는 모든 문자 가능
			else {  // * 표가 아니라면
				if(banned_id[depth][j] == user_id[i][j]) {continue;}    // 같은 문자라면 계속해서 비교
				else {  // 다른 문자라면 불량 사용자의 아이디가 아님
					flag = false;
					break;
				}
			}
		}

		if(flag) {  // 불량 사용자의 아이디가 될 수 있는 경우
			visited[i] = true;  // 불량 사용자 체크
			Dfs(depth+1, user_id, banned_id, userIdNum, bannedIdNum, visited, s);
			visited[i] = false; // 불량 사용자 체크 해제
		}
	}



	return;
}

int solution(std::vector<std::string> user_id, std::vector<std::string> banned_id) {
    int answer = 0;
    
    int userIdNum = user_id.size(); // userIdNum: 이벤트 응모자 아이디의 개수, 1<=userIdNum<=8
	int bannedIdNum = banned_id.size(); // bannedIdNum: 불량 사용자 아이디의 개수, 1<=bannedIdNum<=userIdNum

	std::vector<bool> visited;  // visited[i]: i 번 사용자가 불량 사용자라면 true
	visited.assign(userIdNum, false);

	std::set<std::string> s;    // s: 조합의 개수

	Dfs(0, user_id, banned_id, userIdNum, bannedIdNum, visited, s);
    
	answer = s.size();  // 집합의 크기는 제재 아이디 목록의 개수

    return answer;
}