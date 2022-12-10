#include <climits>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

enum Direction { UP = 'U', DOWN = 'D', LEFT = 'L', RIGHT = 'R' };

template <typename T> int sign(T val) { return (T(0) < val) - (val < T(0)); }

class Coords {
    long x, y;
    enum CoordType { ROW, COL };

    // does not check overflow if abs(val) > 1
    bool checkOF(long val, CoordType type) {
        if (val != LONG_MAX && val != LONG_MIN) {
            switch (type) {
            case CoordType::COL:
                this->x = val;
                break;
            case CoordType::ROW:
                this->y = val;
                break;
            }
            return true;
        }
        return false;
    }

  public:
    Coords(long x, long y) : x(x), y(y) {}

    bool operator==(const Coords &rhs) const {
        return this->x == rhs.x && this->y == rhs.y;
    }
    bool operator<(const Coords &rhs) const {
        return this->x < rhs.x || (this->x == rhs.x && this->y < rhs.y);
    }
    Coords operator-(const Coords &rhs) const {
        return Coords(this->x - rhs.x, this->y - rhs.y);
    }
    Coords operator+(const Coords &rhs) const {
        return Coords(this->x + rhs.x, this->y + rhs.y);
    }

    const size_t getY() const { return this->y; }
    const size_t getX() const { return this->x; }

    bool move(Direction direction) {
        switch (direction) {
        case Direction::DOWN:
            return checkOF(this->y - 1, CoordType::ROW);
        case Direction::UP:
            return checkOF(this->y + 1, CoordType::ROW);
        case Direction::RIGHT:
            return checkOF(this->x + 1, CoordType::COL);
        case Direction::LEFT:
            return checkOF(this->x - 1, CoordType::COL);
        default:
            return false;
        }
    }
    bool move(const Coords &dst) {
        bool valid = true;
        valid &= checkOF(this->y + dst.y, CoordType::ROW);
        valid &= checkOF(this->x + dst.x, CoordType::COL);
        return valid;
    }
    bool moveAbs(const Coords &dst) {
        this->y = dst.y;
        this->x = dst.x;
        return true;
    }

    bool goNear(const Coords &dst) {
        if (this->isAdj(dst))
            return false;
        else {
            Coords distance = dst - *this;
            return this->move(Coords(sign(distance.x), sign(distance.y)));
        }
    }

    const bool isAdj(const Coords &coords) const {
        return abs(this->y - coords.y) <= 1 && abs(this->x - coords.x) <= 1;
    }

    const void print() const {
        cerr << "x=" << this->x << ", y=" << this->y << endl;
    }
};

class Rope {
    vector<Coords> nodes;
    Coords *head, *tail;

  public:
    explicit Rope(size_t length) {
        this->nodes = vector<Coords>(length, Coords(0, 0));
        this->head = &this->nodes.front();
        this->tail = &this->nodes.back();
    }

    Coords move(Direction direction) {
        head->move(direction);
        for (size_t i = 1; i < this->nodes.size(); i++) {
            this->nodes[i].goNear(this->nodes[i - 1]);
        }
        return *this->tail;
    }

    const void print() const {
        cerr << "H: ";
        this->head->print();
        for (size_t i = 1; i < this->nodes.size(); i++) {
            cerr << i << ": ";
            this->nodes[i].print();
        }
        cerr << endl;
    }
};

int solve(size_t size) {
    set<Coords> visited;
    Rope rope(size);

    char direction;
    int movement;
    while (cin >> direction >> movement) {
        for (int i = 0; i < movement; i++) {
            visited.insert(rope.move((Direction)direction));
        }
    }
    return visited.size();
}

int part1() {
    return solve(2);
    // set<Coords> visited;
    // Coords head(0, 0), tail(0, 0);
    //
    // char direction;
    // int movement;
    // while (cin >> direction >> movement) {
    //     for (int i = 0; i < movement; i++) {
    //         Coords prev_head = head;
    //         head.move((Direction)direction);
    //         if (!tail.isAdj(head)) {
    //             tail.moveAbs(prev_head);
    //         }
    //         visited.insert(tail);
    //     }
    // }
    // return visited.size();
}

int part2() { return solve(10); }

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
