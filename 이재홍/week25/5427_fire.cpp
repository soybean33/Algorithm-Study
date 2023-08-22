#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define DIR 4
struct Coordinate {
    int x;
    int y;
    static const Coordinate base_dir[DIR];
    Coordinate(int x, int y): x(x), y(y) {}
    Coordinate operator+(Coordinate rhs) {
        return Coordinate(x + rhs.x, y + rhs.y);
    }
};
const Coordinate Coordinate::base_dir[DIR] = {{ 0, 1}, { 1, 0}, { 0,-1}, {-1, 0}};

enum BuildingValue {
    CHAR_VOID = '.',
    CHAR_WALL = '#',
    CHAR_FIRE = '*',
    CHAR_START = '@',
    VOID = 0,
    WALL = -1,
    FIRE = -1,
    START = 1,
    VISITED = 1
};

struct Building {
    const int height;
    const int width;
    vector<vector<int>>floor;
    queue<Coordinate> fire_queue;
    queue<Coordinate> walk_queue;
    static int field_value[128];
    static void Init() {
        field_value[CHAR_VOID] = VOID;
        field_value[CHAR_WALL] = WALL;
        field_value[CHAR_FIRE] = FIRE;
        field_value[CHAR_START] = START;
    }
    Building(int height, int width): height(height), width(width) {
        floor = vector<vector<int>>(height, vector<int>(width, 0));
        ReadMap();
    }
    void ReadMap() {
        for(int height_it = 0; height_it < height; ++height_it) {
            string str;
            cin >> str;
            for(int width_it = 0; width_it < width; ++width_it) {
                floor[height_it][width_it] = field_value[str[width_it]];
                if(str[width_it] == CHAR_FIRE) {fire_queue.push(Coordinate(width_it, height_it));}
                else if(str[width_it] == CHAR_START) {walk_queue.push(Coordinate(width_it, height_it));}
            }
        }
    }
    void RunWalk() {
        int time_passed = 0;
        while(++time_passed) {
            if(walk_queue.size() == 0) {break;}
            if(RunStep()) {
                cout << time_passed << '\n';
                return;
            }
        }
        cout << "IMPOSSIBLE\n";
    }
    bool RunStep() {
        const bool finished = true;
        const bool not_finished = false;
        int fire_queue_size = fire_queue.size();
        for(int it = 0; it < fire_queue_size; ++it) {
            Coordinate fire_now = fire_queue.front();
            fire_queue.pop();
            for(int dir = 0; dir < DIR; ++dir) {
                Coordinate fire_next = fire_now + Coordinate::base_dir[dir];
                if(OutOfBound(fire_next)) {continue;}
                if(IsTarget(fire_next, WALL)) {continue;}
                SetTarget(fire_next, WALL);
                fire_queue.push(fire_next);
            }
        }
        int walk_queue_size = walk_queue.size();
        for(int it = 0; it < walk_queue_size; ++it) {
            Coordinate walk_now = walk_queue.front();
            walk_queue.pop();
            for(int dir = 0; dir < DIR; ++dir) {
                Coordinate walk_next = walk_now + Coordinate::base_dir[dir];
                if(OutOfBound(walk_next)) {return finished;}
                if(IsTarget(walk_next, WALL)) {continue;}
                if(IsTarget(walk_next, VISITED)) {continue;}
                SetTarget(walk_next, VISITED);
                walk_queue.push(walk_next);
            }
        }
        return not_finished;
    }
    bool OutOfBound(Coordinate &coordinate) {return coordinate.x < 0 || width <= coordinate.x || coordinate.y < 0 || height <= coordinate.y;}
    bool IsTarget(Coordinate &coordinate, const int target) {return floor[coordinate.y][coordinate.x] == target;}
    void SetTarget(Coordinate &coordinate, const int target) {floor[coordinate.y][coordinate.x] = target;}
};
int Building::field_value[128] = {0,};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int testcase;
    cin >> testcase;
    Building::Init();
    for(int case_no = 0; case_no < testcase; ++case_no) {
        int width;
        int height;
        cin >> width >> height;
        Building building{height, width};
        building.RunWalk();
    }
    return 0;
}