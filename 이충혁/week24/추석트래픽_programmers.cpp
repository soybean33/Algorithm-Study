#include<iostream>

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

enum SPACE_STR_INDEX
{
    QUIT_TIME = 1,
    INTERVAL = 2
};

enum COL_STR_INDEX
{
    HOUR = 0,
    MIN = 1,
    SEC = 2
};

int solution(vector<string> lines) {
    int answer = 0;

    // 여기에 문자열을 먼저 spacebar를 기준으로 자른다
    vector<string> space_str;
    space_str.resize(3);

    // : 기준으로 문자열을 한번더 자른다.
    vector<string> col_str;
    col_str.resize(3);

    // 시간을 자르기 위한 변수들
    int hour, min, sec, msec;
    char temp;

    // 시작 종료 시간을 벡터에 저장한뒤 정려할 것이다.
    vector<int> st_times, ed_times;

    for (int i = 0; i < lines.size(); i++)
    {
        istringstream iss(lines[i]);
        string str_temp;

        for (int j = 0; j < 3; j++)
        {
            if (!getline(iss, space_str[j], ' '))
                return 0;
        }

        istringstream quit_time_iss(space_str[QUIT_TIME]);
        quit_time_iss >> hour >> temp >> min >> temp >> sec >> temp >> msec;
        
        int ed_time = hour * 3600000 + min * 60000 + sec * 1000 + msec;

        ed_times.push_back(ed_time);

        if (space_str[INTERVAL].find('.') == string::npos)
        {
            st_times.push_back(ed_time - space_str[INTERVAL][0] * 1000 + 1);
        }
        else
        {
            istringstream interval_time_iss(space_str[INTERVAL]);
            interval_time_iss >> sec >> temp >> msec >> temp;

            st_times.push_back(ed_time - (sec * 1000 + msec) + 1);
        }
    }

    sort(st_times.begin(), st_times.end());
    sort(ed_times.begin(), ed_times.end());

    int time_index = st_times[0] - st_times[0] % 1000;
    int st_index = 0, ed_index = 0;

    int cnt = 0;

    for (time_index; time_index <= ed_times[ed_times.size() - 1]; time_index += 1000)
    {
        if (st_index < st_times.size())
        {
            while (st_times[st_index] <= time_index + 1000)
            {
                cnt++;
                st_index++;
                if (st_index >= st_times.size())
                    break;
            }
        }

        if (ed_index < ed_times.size())
        {
            while (ed_times[ed_index] < time_index)
            {
                cnt--;
                ed_index++;
                if (ed_index >= ed_times.size())
                    break;
            }
        }


        if (cnt > answer)
            answer = cnt;
    }


    return answer;
}

int main()
{
    int ans = 0;

    /*
    ans = solution({"2016-09-15 01:00:04.001 2.0s",
"2016-09-15 01:00:07.000 2s" 
        });

    ans = solution({ "2016-09-15 01:00:04.002 2.0s",
"2016-09-15 01:00:07.000 2s" });
*/

    ans = solution({ "2016-09-15 20:59:57.421 0.351s",
"2016-09-15 20:59:58.233 1.181s",
"2016-09-15 20:59:58.299 0.8s",
"2016-09-15 20:59:58.688 1.041s",
"2016-09-15 20:59:59.591 1.412s",
"2016-09-15 21:00:00.464 1.466s",
"2016-09-15 21:00:00.741 1.581s",
"2016-09-15 21:00:00.748 2.31s",
"2016-09-15 21:00:00.966 0.381s",
"2016-09-15 21:00:02.066 2.62s" });

    cout << ans;

	return 0;
}