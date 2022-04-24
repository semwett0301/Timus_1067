#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;


class Dir {
public:
    string name;
    vector<Dir *> includes_directories;

    Dir(string name) {
        this->name = name;
    }

    Dir* getDir(string name) {
        for (Dir *dir: includes_directories) {
            if (dir->name == name) return dir;
        }

        Dir *new_dir = new Dir(name);
        includes_directories.push_back(new_dir);
        return new_dir;
    }

    bool comp(Dir* dir1, Dir* dir2) {
        return dir1->name > dir2->name;
    }

    void print_dir(string tab, bool comp(Dir*, Dir*)) {
        sort(includes_directories.begin(), includes_directories.end(), comp);
        for (Dir* dir : includes_directories) {
            cout << tab << dir->name << "\n";
            dir->print_dir(tab + " ", comp);
        }
    }
};

bool comp(Dir* dir1, Dir* dir2) {
    return dir1->name < dir2->name;
}

int main() {
    int n;
    cin >> n;
    Dir* root = new Dir("root");
    string s;
    for (int i = 0; i < n + 1; ++i) {
        getline(cin, s);
        stringstream path(s);
        Dir* cur = root;
        while (getline(path, s, '\\')) {
            cur = cur->getDir(s);
        }
    }

    root->print_dir("", comp);
    return 0;
}
