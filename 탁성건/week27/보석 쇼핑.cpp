#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

constexpr int INF = 987654321;

vector<int> solution(vector<string> gems) {
	vector<int> answer = { 0, 0 };

	const int N = gems.size();
	int M = 0;

	unordered_map<string, int> gem2idx;
	vector<int> gemsIdx;

	for (const auto& gem : gems) {
		if (gem2idx.find(gem) == gem2idx.end())
			gem2idx.insert({ gem, M++ });
		gemsIdx.push_back(gem2idx[gem]);
	}

	vector<int> gemsCnt(M);
	int gemTypeCnt = 0;

	int minLen = INF;
	int left = 0;
	int right = 0;

	while (true) {
		if (gemTypeCnt == M) {
			int len = right - left + 1;

			if (len < minLen) {
				minLen = len;
				answer = { left + 1, right };
			}

			if (--gemsCnt[gemsIdx[left]] == 0)
				--gemTypeCnt;

			++left;
		}
		else {
			if (right >= N)
				break;

			if (++gemsCnt[gemsIdx[right]] == 1)
				++gemTypeCnt;

			++right;
		}
	}

	return answer;
}
