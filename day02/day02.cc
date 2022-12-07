#include <iostream>
#include <map>
#include <vector>

using namespace std;

int part1() {
    map<char, int> MOVES = {{'X', 1}, {'Y', 2}, {'Z', 3}};
    map<pair<char, char>, int> COMBS = {
        {make_pair('A', 'X'), 3}, {make_pair('A', 'Y'), 6},
        {make_pair('A', 'Z'), 0}, {make_pair('B', 'X'), 0},
        {make_pair('B', 'Y'), 3}, {make_pair('B', 'Z'), 6},
        {make_pair('C', 'X'), 6}, {make_pair('C', 'Y'), 0},
        {make_pair('C', 'Z'), 3},
    };

    int acc = 0;
    char other, mine;
    while (cin >> other >> mine) {
        acc += COMBS[make_pair(other, mine)] + MOVES[mine];
    }
    return acc;
}

int part2() {
    map<char, int> MOVES = {{'X', 0}, {'Y', 3}, {'Z', 6}};
    map<pair<char, char>, int> COMBS = {
        {make_pair('A', 'X'), 3}, {make_pair('A', 'Y'), 1},
        {make_pair('A', 'Z'), 2}, {make_pair('B', 'X'), 1},
        {make_pair('B', 'Y'), 2}, {make_pair('B', 'Z'), 3},
        {make_pair('C', 'X'), 2}, {make_pair('C', 'Y'), 3},
        {make_pair('C', 'Z'), 1},
    };

    int acc = 0;
    char other, mine;
    while (cin >> other >> mine) {
        acc += COMBS[make_pair(other, mine)] + MOVES[mine];
    }
    return acc;
}

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
