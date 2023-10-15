#include <iostream>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    answer.resize(2);

    unordered_set<string> gem_kind;
    unordered_map<string, int> gem_cnt;
    
    for (auto& str : gems)
    {
        gem_kind.insert(str);
        if (gem_cnt.find(str) != gem_cnt.end())
        {
            gem_cnt.insert({ str, 0 });
        }
    }

    int left = 0;
    int right = 0;
    int min = 21e8;
    int i = 0;

    while (1)
    {
        for (i = right; i < gems.size(); i++)
        {
            gem_cnt[gems[i]]++;

            if (gem_cnt.size() >= gem_kind.size())
            {
                right = i;

                break;
            }
        }

        if (i == gems.size())
        {
            return answer;
        }

        for (i = left; i < gems.size(); ++i)
        {
            if (gem_cnt[gems[i]] == 1)
            {
                left = i;
                break;
            }
            else
            {
                gem_cnt[gems[i]]--;
            }
        }


        if (right - left < min)
        {
            min = right - left;
            answer[0] = left + 1;
            answer[1] = right + 1;
        }

        gem_cnt.erase(gems[left]);

        left++;
        right++;
    }

    return answer;
}


int main()
{
    vector<int> ans;

    ans = solution({ "DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA" });
    /*
    ans = solution({ "AA", "AB", "AC", "AA", "AC" });

    ans = solution({ "XYZ", "XYZ", "XYZ" });

    ans = solution({ "ZZZ", "YYY", "NNNN", "YYY", "BBB" });
    */
    for (auto val : ans)
    {
        cout << val << endl;
    }

    return 0;
}