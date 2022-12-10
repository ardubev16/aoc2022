#include <iostream>
#include <vector>

using namespace std;

enum State { READY, BUSY };

long checkCycle(unsigned long cycle, long x) {
    if (cycle >= 20 && (cycle - 20) % 40 == 0) {
        cerr << cycle << ' ' << x << ' ' << x * cycle << endl;
        return x * cycle;
    }
    return 0;
}

int part1() {
    long x = 1;
    long acc = 0;
    unsigned long cycle = 1;

    string instruction;
    State state = State::READY;
    while (cycle <= 220) {
        acc += checkCycle(cycle, x);
        if (state == State::READY)
            cin >> instruction;

        if (instruction[0] == 'a') {
            if (state == State::READY)
                state = State::BUSY;
            else {
                long num;
                cin >> num;
                x += num;
                state = State::READY;
            }
        }
        cycle++;
    }
    // while (cin >> instruction) {
    //     if (instruction[0] == 'a') {
    //         cycle++;
    //         acc += checkCycle(cycle, x);
    //         long num;
    //         cin >> num;
    //         x += num;
    //     }
    //     cycle++;
    //     acc += checkCycle(cycle, x);
    // }
    return acc;
}

bool inBounds(long val, long bound) { return val >= 0 && val < bound; }

void drawPixel(vector<bool> &row, long x) {
    if (inBounds(x, row.size()))
        row[x] = true;
    if (inBounds(x - 1, row.size()))
        row[x - 1] = true;
    if (inBounds(x + 1, row.size()))
        row[x + 1] = true;
}

void part2() {
    long x = 1;
    unsigned long cycle = 1;
    vector<vector<bool>> screen(6, vector<bool>(40));

    string instruction;
    State state = State::READY;
    while (cycle <= 240) {
        size_t coord_y = (cycle - 1) / 40;
        size_t coord_x = (cycle - 1) % 40;
        vector<bool> row(40, false);

        drawPixel(row, x);

        screen[coord_y][coord_x] = row[coord_x];

        if (state == State::READY)
            cin >> instruction;
        if (instruction[0] == 'a') {
            if (state == State::READY)
                state = State::BUSY;
            else {
                long num;
                cin >> num;
                x += num;
                state = State::READY;
            }
        }
        cycle++;
    }

    for (const vector<bool> &row : screen) {
        for (bool pixel : row) {
            cout << (pixel ? '#' : '.');
        }
        cout << endl;
    }
}

int main() {
    // cout << part1();
    part2();
    return 0;
}
