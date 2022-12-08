#include <algorithm>
#include <iostream>

using namespace std;

bool all_unique(const string &str) {
    for (int i = 0; i < str.size(); i++) {
        for (int j = i + 1; j < str.size(); j++) {
            if (str[i] == str[j])
                return false;
        }
    }
    return true;
}

int part1(int distinct_chars = 4) {
    string str;
    cin >> str;

    for (int i = distinct_chars - 1; i < str.size(); i++) {
        if (all_unique(str.substr(i - (distinct_chars - 1), distinct_chars)))
            return i + 1;
    }
    return -1;
}

int part2() { return part1(14); }

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
