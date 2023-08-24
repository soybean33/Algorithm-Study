#include <iostream>
#include <vector>
using namespace std;

namespace limits {
    template <typename T>
    T max_value = 0;
    template <>
    long long max_value<long long> = 0x7fff'ffff'ffff'ffffLL;
}

namespace utility {
    template <typename T>
    T binary_search(vector<T> &array, T target, T left, T right) {
        while(left < right) {
            T mid = (left + right) >> 1;
            T result = 0LL;
            bool over_target = false;
            for(const T value: array) {
                result += mid / value;
                if(over_target = target <= result) {break;}
            }
            if(over_target) {right = mid; continue;}
            left = mid + 1;
        }
        return left;
    }
}

template <typename T>
class Gate {
private:
    T gates_size_;
    T people_size_;
    vector<T> gates_time_;
public:
    Gate(T gates_size, T people_size): gates_size_(gates_size), people_size_(people_size), gates_time_(vector<T>(gates_size)) {
        ReadGatesTime();
    }
    void ReadGatesTime() {
        for(T &gate_time_: gates_time_) {cin >> gate_time_;}
    }
    T GetMinimumTime() {
        return utility::binary_search<T>(gates_time_, people_size_, 0, limits::max_value<T>);
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    long long gates_size, people_size;
    cin >> gates_size >> people_size;
    Gate<long long> gate{gates_size, people_size};
    cout << gate.GetMinimumTime();
    return 0;
}