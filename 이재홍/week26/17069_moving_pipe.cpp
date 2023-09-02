#include <iostream>
#include <vector>

using namespace std;

struct PipeCount {
    long long pipe_count[3];
    PipeCount(): pipe_count{0, 0, 0} {}
    long long &operator[](size_t index) {return pipe_count[index];}
    template <typename... Targs>
    long long GetSum(Targs... args) {return (pipe_count[args] + ...);}
};

enum PipeState {
    HORIZONTAL = 0,
    DIAGONAL = 1,
    VERTICAL = 2
};

class Field {
private:
    int size_;
    vector<vector<int>> map_;
    vector<vector<PipeCount>> count_;
public:
    Field(int size):
        size_(size),
        map_(vector<vector<int>>(size, vector<int>(size, 0LL))),
        count_(vector<vector<PipeCount>>(size, vector<PipeCount>(size)))
    {}
    void ReadMap() {
        for(vector<int> &row: map_) {
            for(int &element: row) {
                cin >> element;
            }
        }
    }
    void Count() {
        count_[0][1][HORIZONTAL] = 1LL;
        for(int col_it = 2; col_it < size_; ++col_it) {
            count_[0][col_it][HORIZONTAL] = count_[0][col_it - 1][HORIZONTAL] & GetMask(map_[0][col_it]);
        }
        for(int row_it = 1; row_it < size_; ++row_it) {
            for(int col_it = 2; col_it < size_; ++col_it) {
                count_[row_it][col_it][HORIZONTAL] = count_[row_it][col_it - 1].GetSum(HORIZONTAL, DIAGONAL) & GetMask(map_[row_it][col_it - 1], map_[row_it][col_it]);
                count_[row_it][col_it][DIAGONAL] = count_[row_it - 1][col_it - 1].GetSum(HORIZONTAL, DIAGONAL, VERTICAL) & GetMask(map_[row_it - 1][col_it - 1], map_[row_it - 1][col_it], map_[row_it][col_it - 1], map_[row_it][col_it]);
                count_[row_it][col_it][VERTICAL] = count_[row_it - 1][col_it].GetSum(DIAGONAL, VERTICAL) & GetMask(map_[row_it - 1][col_it], map_[row_it][col_it]);
            }
        }
    }
    template <typename... Targs>
    long long GetMask(Targs... map_state) {return 0LL - !(map_state | ...);}
    long long GetResult() {return count_[size_ - 1][size_ - 1].GetSum(HORIZONTAL, DIAGONAL, VERTICAL);}
};

int main() {
    // initiate fast io
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int size;
    cin >> size;
    Field field{size};
    field.ReadMap();
    field.Count();
    cout << field.GetResult();
    return 0;
}