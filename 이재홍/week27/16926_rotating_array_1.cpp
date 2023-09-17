#include <iostream>
#include <vector>

using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate(): x(), y() {}
    Coordinate(int x, int y): x(x), y(y) {}
    Coordinate operator+(const Coordinate& rhs) {return {x + rhs.x, y + rhs.y};}
    Coordinate &operator+=(const Coordinate& rhs) {x += rhs.x; y += rhs.y; return *this;}
    bool operator!=(Coordinate& rhs) {return x != rhs.x || y != rhs.y;}
};

class RotatableArray {
private:
    int rows_;
    int columns_;
    int layers_;
    vector<vector<Coordinate>> mapping_;
    vector<vector<int>> data_;
public:
    RotatableArray(int rows, int columns):
        rows_(rows),
        columns_(columns),
        layers_(rows < columns ? (rows >> 1) : (columns >> 1)),
        mapping_(vector<vector<Coordinate>>(rows, vector<Coordinate>(columns))),
        data_(vector<vector<int>>(layers_, vector<int>()))
    {
        const Coordinate direction[4]{{ 1, 0}, { 0, 1}, {-1, 0}, { 0,-1}};
        const int directions = 4;
        Coordinate corner[4]{{columns_ - 1, 0}, {columns_ - 1, rows_ - 1}, {0, rows_ - 1}, {0, 0}};
        const Coordinate corner_add[4]{{-1, 1}, {-1,-1}, { 1,-1}, { 1, 1}};
        for(int layer_it = 0; layer_it < layers_; ++layer_it) {
            Coordinate now{corner[3]};
            int index{0};
            for(int direction_it = 0; direction_it < directions; ++direction_it) {
                while(now != corner[direction_it]) {
                    mapping_[now.y][now.x] = {index++, layer_it};
                    now += direction[direction_it];
                }
                corner[direction_it] += corner_add[direction_it];
            }
            data_[layer_it] = vector<int>(index);
        }
        ReadData();
    }
    void ReadData() {
        for(int rows_it = 0; rows_it < rows_; ++rows_it) {
            for(int columns_it = 0; columns_it < columns_; ++columns_it) {
                const Coordinate &map_to = mapping_[rows_it][columns_it];
                cin >> data_[map_to.y][map_to.x];
            }
        }
    }
    void PrintData(int rotation) {
        for(int rows_it = 0; rows_it < rows_; ++rows_it) {
            for(int columns_it = 0; columns_it < columns_; ++columns_it) {
                const Coordinate &map_to = mapping_[rows_it][columns_it];
                const int data_layer_size = data_[map_to.y].size();
                cout << data_[map_to.y][(map_to.x + rotation) % data_layer_size] << ' ';
            }
            cout << '\n';
        }
    }
};

int main() {
    // initiate fast io
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int rows, columns, rotation;
    cin >> rows >> columns >> rotation;
    RotatableArray rotatable_array{rows, columns};
    rotatable_array.PrintData(rotation);
    return 0;
}