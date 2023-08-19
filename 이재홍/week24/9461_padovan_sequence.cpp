#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T, N;
    for(cin >> T; 0 < T; --T) {
        cin >> N;
        int first_index = 1;
        long long sequence[5] = {1LL, 1LL, 1LL, 2LL, 2LL};
        long long (&s)[5] = sequence;
        while(5 <= N - first_index) {
            first_index += 5;
            s[4] += s[3] += s[2] += s[1] += s[0] += s[4];
        }
        cout << s[N - first_index] << '\n';
    }
    return 0;
}