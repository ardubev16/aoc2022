#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int part1() {
    int maxValue = 0;
    int acc = 0;
    while (!cin.eof()) {
        string numBuf;
        getline(cin, numBuf);
        if (numBuf.empty()) {
            maxValue = max(maxValue, acc);
            acc = 0;
        } else
            acc += stoi(numBuf);
    }
    return maxValue;
}

int part2() {
    vector<int> calories;
    int acc = 0;

    while (!cin.eof()) {
        string numBuf;
        getline(cin, numBuf);
        if (numBuf.empty()) {
            calories.push_back(acc);
            acc = 0;
        } else
            acc += stoi(numBuf);
    }
    sort(calories.begin(), calories.end(), [](int i, int j) { return i > j; });
    return calories[0] + calories[1] + calories[2];
}

int main() {
    // cout << "Sol1: " << part1();
    cout << "Sol2: " << part2();
    return 0;
}
