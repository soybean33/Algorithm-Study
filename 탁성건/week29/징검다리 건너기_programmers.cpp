#include <algorithm>
#include <vector>
using namespace std;

constexpr int INF = 21e8;

int solution(vector<int> stones, int k) {
    int left = *min_element(stones.begin(), stones.end());
    int right = *max_element(stones.begin(), stones.end());
    int ans = left;

    stones.push_back(INF);

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int prev = -1;
        bool valid = true;

        for (int i = 0; i < stones.size(); ++i) {
            if (stones[i] < mid)
                continue;

            if (i - prev > k) {
                valid = false;
                break;
            }

            prev = i;
        }

        if (valid) {
            ans = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }

    return ans;
}
