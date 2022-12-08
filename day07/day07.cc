#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

enum Ftype { D, F };

class Node {
    unordered_map<string, Node> children;
    string name;
    Node *parent;
    Ftype type;
    long size;

  public:
    Node(Ftype type, const string &name, Node *parent, long size = 0) {
        this->type = type;
        this->size = size;
        this->parent = parent;
        this->name = name;
    }

    unordered_map<string, Node> &getChildren() { return this->children; }
    const Ftype getType() const { return this->type; }
    const string &getName() const { return this->name; }

    const long getSize() const {
        if (this->size == 0) {
            long sizeSum = 0;
            for_each(this->children.begin(), this->children.end(),
                     [&sizeSum](const pair<string, Node> &node) {
                         sizeSum += node.second.getSize();
                     });
            return sizeSum;
        } else
            return this->size;
    }
    const void updateSize() { this->size = this->getSize(); }

    Node *getParent() const { return this->parent; }

    const Node *newDir(string dir_name) {
        this->children.insert(
            make_pair(dir_name, Node(Ftype::D, dir_name, this)));
        return &this->children.at(dir_name);
    }
    const Node *newFile(string file_name, long size) {
        this->children.insert(
            make_pair(file_name, Node(Ftype::F, file_name, this, size)));
        return &this->children.at(file_name);
    }

    const void print(int lvl = 0) const {
        string _type = this->type == Ftype::F ? "file" : "dir";
        cerr << string(lvl * 2, ' ') + "- " + this->name + " (" + _type +
                    ", size=" + to_string(this->getSize()) + ')'
             << endl;
        for (pair<string, Node> node : children)
            node.second.print(lvl + 1);
    }
};

Node *handleCd(Node *curr_dir) {
    string dir_name;
    cin >> dir_name;

    Node *new_dir = curr_dir;
    if (dir_name.compare("..") == 0)
        new_dir = curr_dir->getParent();
    else if (dir_name.compare("/") != 0)
        new_dir = &curr_dir->getChildren().at(dir_name);

    return new_dir;
}

void handleLs(Node *curr_dir, string dim_dir) {
    string filename;
    cin >> filename;

    if (dim_dir[0] == 'd') {
        curr_dir->newDir(filename);
    } else {
        curr_dir->newFile(filename, stol(dim_dir));
    }
}

Node readInput() {
    Node root_dir(Ftype::D, "/", nullptr);
    string buf;

    Node *curr_dir = &root_dir;

    while (cin >> buf) {
        if (buf[0] == '$') {
            cin >> buf;
            if (buf[0] == 'c')
                curr_dir = handleCd(curr_dir);
        } else
            handleLs(curr_dir, buf);
    }
    root_dir.updateSize();
    return root_dir;
}

int part1() {
    const int UPPER_BOND = 100000;

    Node root_dir = readInput();
    // root_dir.print();

    int acc = 0;
    queue<Node> Q;
    Q.push(root_dir);
    while (!Q.empty()) {
        Node curr_dir = Q.front();
        Q.pop();
        for (const pair<string, Node> &subdir : curr_dir.getChildren()) {
            if (subdir.second.getType() == Ftype::D) {
                Q.push(subdir.second);
                if (subdir.second.getSize() <= UPPER_BOND)
                    acc += subdir.second.getSize();
            }
        }
    }
    return acc;
}

int part2() {
    const int TOT_NEEDED = 30000000;
    const int TOTAL = 70000000;

    Node root_dir = readInput();
    // root_dir.print();

    int free = TOTAL - root_dir.getSize();
    int needed = TOT_NEEDED - free;
    long min_dir = INT_MAX;
    queue<Node> Q;
    Q.push(root_dir);
    while (!Q.empty()) {
        Node curr_dir = Q.front();
        Q.pop();
        for (const pair<string, Node> &subdir : curr_dir.getChildren()) {
            if (subdir.second.getType() == Ftype::D) {
                Q.push(subdir.second);
                if (subdir.second.getSize() >= needed)
                    min_dir = min(min_dir, subdir.second.getSize());
            }
        }
    }
    return min_dir;
}

int main() {
    // cout << part1();
    cout << part2();
    return 0;
}
