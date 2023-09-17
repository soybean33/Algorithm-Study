#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int size;
    cin >> size;
    vector<int> values = vector<int>(size);
    for(int &value: values) {cin >> value;}
    sort(values.begin(), values.end());
    int sum = 0;
    int it;
    for(it = size - 2; 0 <= it && 1 < values[it]; it -= 2) {sum += values[it] * values[it + 1];}
    if(-1 <= it && it & 1) {sum += values[it + 1]; it ^= it & 1;}
    while(0 <= it && 0 < values[it + 1]) {sum += values[it] + values[it + 1]; it -= 2;}
    for(; 0 <= it; it -= 2) {sum += values[it] * values[it + 1];}
    cout << sum;
    return 0;
}