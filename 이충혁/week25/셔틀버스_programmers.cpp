#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string time_to_int(int t)
{
    char tmp[6];

    sprintf(tmp, "%02d:%02d", t / 60, t % 60);

    return string(tmp);
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";

    vector <int> time;
    time.resize(timetable.size());

    for (int i = 0; i < timetable.size(); i++)
    {
        int hour, min;
        char tmp;
        istringstream iss(timetable[i]);
        iss >> hour >> tmp >> min;
        time[i] = hour * 60 + min;
    }
    
    sort(time.begin(), time.end());

    int cur_time = 9 * 60;
    int crew_index = 0;
    int wait = 0;

    for (int i = n; i > 1; i--)
    {
        for (; crew_index < time.size() && time[crew_index] <= cur_time; crew_index++, wait++);

        if (wait > m)
            wait = wait - m;
        else
            wait = 0;

        cur_time += t;
    }

    for (; crew_index < time.size() && time[crew_index] <= cur_time; crew_index++, wait++);

    if (wait < m)
        return time_to_int(cur_time);

    return time_to_int(time[crew_index - (wait - m) - 1] - 1);
}

int main()
{
    string ans;

    //ans = solution(1, 1, 5, {"08:00", "08:01", "08:02", "08:03"});
    ans = solution(2, 10, 2, { "09:10", "09:09", "08:00"});
    /*
    ans = solution(2, 1, 2, { "09:00", "09:00", "09:00", "09:00" });
    ans = solution(1, 1, 5, { "00:01", "00:01", "00:01", "00:01", "00:01" });
    ans = solution(1, 1, 1, { "23:59" });
    ans = solution(10, 60, 45, { "23:59","23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59" });
    */
    cout << ans;


	return 0;
}