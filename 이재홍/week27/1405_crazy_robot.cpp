// self-avoiding walks

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate(int x, int y): x(x), y(y) {}
    Coordinate operator+(Coordinate &rhs) {return {x + rhs.x, y + rhs.y};}
    Coordinate &operator+=(const Coordinate &rhs) {x += rhs.x; y += rhs.y; return *this;}
};

enum Direction {
    EAST = 0,
    SOUTH = 1,
    WEST = 2,
    NORTH = 3
};

class SelfAvoidingWalks {
private:
    int moves_;
    long double odds_[4];
    long double odds_base_;
    long double probability_;
    const bool VISITED = true;
    const bool UNVISITED = false;
    vector<vector<long double>> cummulative_odds_;
    vector<vector<bool>> field_;
    Coordinate now_;
    const Coordinate cord_dir[4]{{ 1, 0}, { 0, 1}, {-1, 0}, { 0,-1}};
    int moves_count_ = 0;
public:
    SelfAvoidingWalks(int moves, vector<long double> &odds):
        moves_(moves),
        odds_{odds[0], odds[2], odds[1], odds[3]},
        odds_base_(100),
        probability_(1.0L),
        cummulative_odds_(vector<vector<long double>>(4, vector<long double>(1, 1.0L))),
        field_(vector<vector<bool>>(1 + (moves << 1), vector<bool>(1 + (moves << 1), UNVISITED))),
        now_({moves, moves})
    {}
    long double GetProbability() {return probability_;}
    void CalculateProbability() {
        moves_count_ = 0;
        SetElement(VISITED);
        MoveNow(EAST);
        SetElement(VISITED);
        DFS();
    }
    void DFS() {
        if(moves_ <= moves_count_) {return;}
        for(int direction = EAST; direction <= NORTH; ++direction) {
            MoveNow((Direction)direction);
            if(GetElement()) {
                probability_ = probability_ - cummulative_odds_[0].back() - cummulative_odds_[1].back() - cummulative_odds_[2].back() - cummulative_odds_[3].back();
                UnmoveNow((Direction)direction);
                continue;
            }
            SetElement(VISITED);
            DFS();
            SetElement(UNVISITED);
            UnmoveNow((Direction)direction);
        }
    }
    bool GetElement() {return field_[now_.y][now_.x];}
    void SetElement(bool value) {field_[now_.y][now_.x] = value;}
    void MoveNow(Direction direction) {
        now_ += cord_dir[direction];
        int rotated_direction = direction;
        cummulative_odds_[0].push_back(cummulative_odds_[0].back() * odds_[rotated_direction] / odds_base_);
        rotated_direction = (rotated_direction + 1) % 4;
        cummulative_odds_[1].push_back(cummulative_odds_[1].back() * odds_[rotated_direction] / odds_base_);
        rotated_direction = (rotated_direction + 1) % 4;
        cummulative_odds_[2].push_back(cummulative_odds_[2].back() * odds_[rotated_direction] / odds_base_);
        rotated_direction = (rotated_direction + 1) % 4;
        cummulative_odds_[3].push_back(cummulative_odds_[3].back() * odds_[rotated_direction] / odds_base_);
        moves_count_ += 1;
    }
    void UnmoveNow(Direction direction) {
        now_ += cord_dir[((int)direction + 2) % 4];
        cummulative_odds_[0].pop_back();
        cummulative_odds_[1].pop_back();
        cummulative_odds_[2].pop_back();
        cummulative_odds_[3].pop_back();
        moves_count_ -= 1;
    }
};

int main() {
    int moves;
    vector<long double> odds = vector<long double>(4, 0);
    cin >> moves >> odds[0] >> odds[1] >> odds[2] >> odds[3];
    SelfAvoidingWalks walk{moves, odds};
    walk.CalculateProbability();
    cout.precision(9);
    cout << walk.GetProbability();
    return 0;
}