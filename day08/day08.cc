#include <cassert>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Coords {
    size_t row, col;
    enum CoordType { ROW, COL };

    bool checkLimit(size_t val, size_t limit, CoordType type) {
        if (val < limit) {
            switch (type) {
            case CoordType::COL:
                this->col = val;
                break;
            case CoordType::ROW:
                this->row = val;
                break;
            }
            return true;
        }
        return false;
    }

  public:
    Coords(size_t row, size_t col) : row(row), col(col) {}

    bool operator==(const Coords &rhs) const {
        return this->col == rhs.col && this->row == rhs.row;
    }
    bool operator<(const Coords &rhs) const {
        return this->col < rhs.col ||
               (this->col == rhs.col && this->row < rhs.row);
    }
    size_t operator-(const Coords &rhs) const {
        return abs((long)(this->row - rhs.row)) +
               abs((long)(this->col - rhs.col));
    }

    const size_t getRow() const { return this->row; }
    const size_t getCol() const { return this->col; }

    bool goDown(size_t limit) {
        return checkLimit(this->row + 1, limit, CoordType::ROW);
    }
    bool goUp(size_t limit) {
        return checkLimit(this->row - 1, limit, CoordType::ROW);
    }
    bool goRight(size_t limit) {
        return checkLimit(this->col + 1, limit, CoordType::COL);
    }
    bool goLeft(size_t limit) {
        return checkLimit(this->col - 1, limit, CoordType::COL);
    }
    template <typename T> const T index(vector<vector<T>> mat) const {
        return mat.at(row).at(col);
    }

    const void print() const {
        cerr << "row=" << this->row << ", col=" << this->col << endl;
    }
};

vector<vector<int>> getInput() {
    vector<vector<int>> input;
    string buf;
    while (cin >> buf) {
        vector<int> tmpVec(buf.size());
        for (size_t i = 0; i < tmpVec.size(); i++) {
            tmpVec[i] = buf[i] - '0';
        }
        input.push_back(tmpVec);
    }
    return input;
}

void analizeLeft(const vector<vector<int>> &input, set<Coords> &visible) {
    for (size_t row = 1; row < input.size() - 1; row++) {
        int curr_max = 0;
        for (size_t col = 1; col < input.size() - 1; col++) {
            int curr_input = input[row][col];
            curr_max = max(curr_max, input[row][col - 1]);
            if (curr_max < curr_input)
                visible.insert({row, col});
        }
    }
}

void analizeTop(const vector<vector<int>> &input, set<Coords> &visible) {
    for (size_t col = 1; col < input.size() - 1; col++) {
        int curr_max = 0;
        for (size_t row = 1; row < input.size() - 1; row++) {
            int curr_input = input[row][col];
            curr_max = max(curr_max, input[row - 1][col]);
            if (curr_max < curr_input)
                visible.insert({row, col});
        }
    }
}

void analizeRight(const vector<vector<int>> &input, set<Coords> &visible) {
    for (size_t row = input.size() - 2; row > 0; row--) {
        int curr_max = 0;
        for (size_t col = input.size() - 2; col > 0; col--) {
            int curr_input = input[row][col];
            curr_max = max(curr_max, input[row][col + 1]);
            if (curr_max < curr_input)
                visible.insert({row, col});
        }
    }
}

void analizeBottom(const vector<vector<int>> &input, set<Coords> &visible) {
    for (size_t col = input.size() - 2; col > 0; col--) {
        int curr_max = 0;
        for (size_t row = input.size() - 2; row > 0; row--) {
            int curr_input = input[row][col];
            curr_max = max(curr_max, input[row + 1][col]);
            if (curr_max < curr_input)
                visible.insert({row, col});
        }
    }
}

int part1() {
    vector<vector<int>> input = getInput();

    set<Coords> visible;
    analizeLeft(input, visible);
    analizeTop(input, visible);
    analizeRight(input, visible);
    analizeBottom(input, visible);

    return visible.size() + (input.size() - 1) * 4;
}

bool inside(const Coords &coords, size_t max_size) {
    return coords.getCol() < max_size && coords.getRow() < max_size;
}

int analizeDirections(const vector<vector<int>> &input, const Coords &coords) {
    size_t max_size = input.size();
    int to_check = coords.index(input);

    Coords up = coords, down = coords, left = coords, right = coords;
    while (up.goUp(max_size) && to_check > up.index(input))
        ;
    while (down.goDown(max_size) && to_check > down.index(input))
        ;
    while (left.goLeft(max_size) && to_check > left.index(input))
        ;
    while (right.goRight(max_size) && to_check > right.index(input))
        ;

    return (coords - up) * (coords - down) * (coords - left) * (coords - right);
}

int part2() {
    vector<vector<int>> input = getInput();

    int curr_max = 0;
    for (size_t row = 1; row < input.size() - 1; row++) {
        for (size_t col = 1; col < input.size() - 1; col++) {
            curr_max = max(curr_max, analizeDirections(input, {row, col}));
        }
    }

    return curr_max;
}

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
