#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Logging {
    const int size;
    vector<long long> woods;
    Logging(int size): size(size + 1) {
        woods = vector<long long>(this->size);
        woods.pop_back();
        ReadHeights();
        sort(woods.begin(), woods.end(), greater<long long>());
        woods.push_back(0);
    }
    void ReadHeights() {
        for(long long &wood: woods) {cin >> wood;}
    }
    long long GetMaxHeight(long long target) {
        long long wood_length = 0;
        long long wood_length_next = 0;
        for(long long number_of_woods = 1; number_of_woods <= size; ++number_of_woods) {
            long long height_diff = woods[number_of_woods - 1] - woods[number_of_woods];
            wood_length_next = wood_length + number_of_woods * height_diff;
            if(wood_length_next < target) {
                wood_length = wood_length_next;
                continue;
            }
            return woods[number_of_woods] + (wood_length_next - target) / number_of_woods;
        }
        const int not_valid = -1;
        return not_valid;
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int size;
    long long target_length;
    cin >> size >> target_length;
    Logging logging{size};
    cout << logging.GetMaxHeight(target_length);
    return 0;
}