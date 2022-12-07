#include <iostream>
#include <map>

using namespace std;

int part1() {
    string str;
    int acc = 0;

    while (cin >> str) {
        map<char, bool> visited;
        string first_substr = str.substr(0, str.size() / 2);
        string second_substr = str.substr(str.size() / 2, str.size());

        for (char c : first_substr) {
            if (second_substr.find(c) != string::npos && !visited.count(c)) {
                visited.insert(make_pair(c, true));
                if (isupper(c))
                    acc += c - 'A' + 27;
                else
                    acc += c - 'a' + 1;
            }
        }
    }
    return acc;
}

int part2() {
    string str1, str2, str3;
    int acc = 0;

    while (cin >> str1 >> str2 >> str3) {
        map<char, bool> visited;

        for (char c : str1) {
            if (str2.find(c) != string::npos && str3.find(c) != string::npos &&
                !visited.count(c)) {
                visited.insert(make_pair(c, true));
                if (isupper(c))
                    acc += c - 'A' + 27;
                else
                    acc += c - 'a' + 1;
            }
        }
    }
    return acc;
}

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
