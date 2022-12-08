#include <deque>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<deque<char>> read_stacks() {
    vector<deque<char>> stacks;
    string buf;
    do {
        getline(cin, buf);
        for (size_t i = 0; i < buf.size(); i += 4) {
            if (buf[i] == '[') {
                if (i / 4 + 1 > stacks.size()) {
                    stacks.resize(i / 4 + 1);
                }
                stacks[i / 4].push_back(buf[i + 1]);
            }
        }
    } while (buf[1] != '1');
    return stacks;
}

string part1() {
    vector<deque<char>> stacks = read_stacks();

    int n, src, dst;
    string ignore;
    while (cin >> ignore >> n >> ignore >> src >> ignore >> dst) {
        for (int i = 0; i < n; i++) {
            char to_move = stacks[src - 1].front();
            stacks[src - 1].pop_front();
            stacks[dst - 1].push_front(to_move);
        }
    }
    string result;
    for (size_t i = 0; i < stacks.size(); i++)
        result += stacks[i].front();

    return result;
}

string part2() {
    vector<deque<char>> stacks = read_stacks();

    int n, src, dst;
    string ignore;
    while (cin >> ignore >> n >> ignore >> src >> ignore >> dst) {
        stack<char> tmpQ;
        for (int i = 0; i < n; i++) {
            char to_move = stacks[src - 1].front();
            stacks[src - 1].pop_front();
            tmpQ.push(to_move);
        }
        while (!tmpQ.empty()) {
            stacks[dst - 1].push_front(tmpQ.top());
            tmpQ.pop();
        }
    }
    string result;
    for (size_t i = 0; i < stacks.size(); i++)
        result += stacks[i].front();

    return result;
}

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
