#include <string>
#include <vector>
#include <algorithm>

std::vector<int> minuteTime;    // minuteTime: timetable을 분으로 바꿔서 저장
int resultTime;	// resultTime: 정답 시간

void solution(int n, int t, int m) {
    std::sort(minuteTime.begin(), minuteTime.end());    // 오름차순 정렬
    
    int index = 0;  // index: 이번에 탐승할 크루의 번호
    int busTime = 540;  // busTime: 버스가 정류장에 도착하는 시간 -> 버스는 9:00 에 처음 출발
    
    for(int i=0; i<n; ++i) {
        
        if(i==n-1) {    // 마지막 버스를 타야함
            resultTime = busTime;   // 마지막 버스의 도착 시간
            
            if(minuteTime.size() - index + 1 > m) { // 버스정류장에 탑승 인원보다 많은 사람이 있다면   
                resultTime = std::min(resultTime, minuteTime[index + m - 1] - 1);   // 탑승 인원의 마지막 보다 1분만 빨리 오면 됨
            }
            return;
        }
        
        int rideCrew = 0;    // rideCrew: 버스에 탑승한 크루의 수
        for(int j=0; j<m; ++j) {
            if(busTime < minuteTime[index]) break;  // 버스가 떠난 후 도착한 크루는 탑승할 수 없음
            if(rideCrew >= m) break;    // 버스 탑승 인원 이상 탑승할 수 없음
            
            ++rideCrew;
            ++index;
        }
        busTime += t;   // 다음 버스 시간으로 갱신
    }
    
    return;
}

void input(std::vector<std::string>& timetable) {
    
    int timetableSize = timetable.size();   // timetableSize: 타임테이블의 크기
    
    minuteTime.assign(timetableSize, 0);
    
    for(int i=0; i<timetableSize; ++i) {
        int tmpTime = 0;    // tmpTime: 00:00 형태를 분으로 변경하는 임시 변수
        
        tmpTime += std::stoi(timetable[i].substr(0, 2)) * 60;
        tmpTime += std::stoi(timetable[i].substr(3, 2));
        
        minuteTime[i] = tmpTime;    // 분으로 변경하여 저장
    }
    
    return;
}

std::string solution(int n, int t, int m, std::vector<std::string> timetable) { // n: 셔틀 운행 횟수, t: 셔틀 운행 간격, m: 한 셔틀에 탈 수 있는 최대 크루 수, timetable[i]: i 번째 크루가 대기열에 도착하는 시각
    std::string answer = "";
    
    input(timetable);
    
    solution(n, t, m);
    
    if(resultTime / 60 < 10) answer += '0'; // 시각이 한 자리 수라면 0을 붙힘
    answer += std::to_string(resultTime / 60);
    answer += ':';
    
    if(resultTime % 60 < 10) answer += '0'; // 분이 한 자리 수라면 0을 붙힘
    answer += std::to_string(resultTime % 60);
    
    return answer;
}