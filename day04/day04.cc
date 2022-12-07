#include <iostream>

using namespace std;

pair<string, string> split(const string &str, char delimiter) {
    int delim_pos = str.find(delimiter);
    string substr_1 = str.substr(0, delim_pos);
    string substr_2 = str.substr(delim_pos + 1, str.size());

    return make_pair(substr_1, substr_2);
}

pair<int, int> pairToInt(const pair<string, string> &pairIn) {
    return make_pair(stoi(pairIn.first), stoi(pairIn.second));
}

int part1() {
    string str;
    int cnt = 0;
    while (cin >> str) {
        pair<string, string> substr = split(str, ',');

        pair<int, int> int1 = pairToInt(split(substr.first, '-'));
        pair<int, int> int2 = pairToInt(split(substr.second, '-'));

        if ((int1.first <= int2.first && int1.second >= int2.second) ||
            (int1.first >= int2.first && int1.second <= int2.second))
            cnt++;
    }
    return cnt;
}

int part2() {
    string str;
    int cnt = 0;
    while (cin >> str) {
        pair<string, string> substr = split(str, ',');

        pair<int, int> int1 = pairToInt(split(substr.first, '-'));
        pair<int, int> int2 = pairToInt(split(substr.second, '-'));

        if (!(int1.second < int2.first || int2.second < int1.first))
            cnt++;
    }
    return cnt;
}

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
