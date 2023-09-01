#include <iostream>
using namespace std;

int jumper(int x) {
    if(1 < x) {
        int x_3 = jumper(x / 3) + x % 3;
        int x_2 = jumper(x / 2) + x % 2;
        return min(x_3, x_2) + 1;
    }
    return 0;
}

int main() {
    int N;
    cin >> N;
    cout << jumper(N) << '\n';
    return 0;
}