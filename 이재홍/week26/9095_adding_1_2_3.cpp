#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class PartialVector {
private:
    size_t size_;
    size_t start_;
    size_t end_;
    vector<T> data_;
public:
    PartialVector(size_t size, size_t start): size_(size), start_(start), end_(start + size), data_(vector<T>(size)) {}
    T &operator[](size_t index) {return data_[index - start_];}
    size_t size() {return size_;}
    size_t start() {return start_;}
    size_t end() {return end_;}
};

template <typename T>
class DP {
private:
    T result_;
    vector<PartialVector<T>> data_;
public:
    DP(T target_number) {
        size_t start = target_number;
        size_t end = target_number + 1;
        const T base_[7] = {1, 1, 2, 4, 7, 13, 24};
        if(target_number < 7) {result_ = base_[target_number]; return;}
        while(3 < start) {
            end = ((end - 1) >> 1) + 1;
            start = end - 4;
            data_.emplace_back(4, start);
        }
        PartialVector<T> &last = data_.back();
        size_t last_end = last.end();
        for(size_t it = last.start(); it < last_end; ++it) {
            last[it] = base_[it];
        }
        for(size_t rit = data_.size() - 1; 0 < rit; --rit) {
            PartialVector<T> &former = data_[rit - 1];
            PartialVector<T> &latter = data_[rit];
            GetNextSequence(latter, former);
        }
        GetSingleValue(data_[0], result_, target_number);
    }
    void GetNextSequence(PartialVector<T> &base, PartialVector<T> &result) {
        size_t start = result.start();
        GetSingleValue(base, result[start + 1], start + 1);
        GetSingleValue(base, result[start + 2], start + 2);
        GetSingleValue(base, result[start + 3], start + 3);
        result[start] = result[start + 3] - result[start + 2] - result[start + 1];
    }
    void GetSingleValue(PartialVector<T> &base, T &result, size_t target) {
        size_t half = target >> 1;
        if(target & 1) {
            result = base[half] * base[half] + 2 * base[half] * base[half - 1] + 2 * base[half] * base[half - 2] + base[half - 1] * base[half - 1];
            return;
        }
        result = base[half] * base[half] + base[half - 1] * base[half - 1] + 2 * base[half - 1] * base[half - 2];
        return;
    }
    T GetResult() {return result_;}
};

int main() {
    int testcases;
    cin >> testcases;
    for(int testcase = 1; testcase <= testcases; ++testcase) {
        long long target;
        cin >> target;
        DP<long long> dp(target);
        cout << dp.GetResult() << '\n';
    }
}