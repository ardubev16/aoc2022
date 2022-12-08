#include <iostream>
#include <set>

using namespace std;

int part1() {
    string str;
    int acc = 0;

    while (cin >> str) {
        set<char> visited;
        string first_substr = str.substr(0, str.size() / 2);
        string second_substr = str.substr(str.size() / 2);

        for (char c : first_substr) {
            if (second_substr.find(c) != string::npos && !visited.count(c)) {
                visited.insert(c);
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
        set<char> visited;

        for (char c : str1) {
            if (str2.find(c) != string::npos && str3.find(c) != string::npos &&
                !visited.count(c)) {
                visited.insert(c);
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
