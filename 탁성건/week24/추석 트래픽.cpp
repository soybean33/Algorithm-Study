#include <queue>
#include <string>
#include <vector>
using namespace std;

int solution(vector<string> lines) {
  const int N = lines.size();

  vector<int> startTime(N);
  vector<int> endTime(N);

  for (int i = 0; i < N; ++i) {
    int h, m;
    double s, t;
    sscanf(lines[i].c_str(), "2016-09-15 %d:%d:%lf %lfs", &h, &m, &s, &t);

    endTime[i] = (((h * 60) + m) * 60 + s) * 1000;
    startTime[i] = endTime[i] - t * 1000 + 1;
  }

  priority_queue<int> pq;
  int idx = N - 1;
  int ans = 1;

  while (idx >= 0) {
    while (!pq.empty() && endTime[idx] + 1000 <= pq.top())
      pq.pop();

    pq.push(startTime[idx--]);
    ans = ans > pq.size() ? ans : pq.size();
  }

  return ans;
}
