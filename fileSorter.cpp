/*

Very ugly sorry mess
Will optimize as much as possible :)

*/

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <set>
#include <map>

using namespace std;
using namespace std::filesystem;

void removeEmptyDir(const path& dir) {
    if (!exists(dir) || !is_directory(dir)) { return; }

    for (const auto& entry: directory_iterator(dir)) {
        if (is_directory(entry)) { removeEmptyDir(entry.path()); }
    }

    if (filesystem::is_empty(dir)) {
        cout << "Removing empty directory: " << dir << endl;
        remove(dir);
    }
}

int main() {
    // Change these two for source and destination directories 
    path sourceDir = "/mnt/c/Users/Asian/OneDrive/Desktop/everything else";
    path destinationDir = "/mnt/c/Users/Asian/OneDrive/Desktop";

    vector<directory_entry> entryList;
    set<path> extensions;
    map<path, path> extensionMap;

    if (exists(sourceDir) && is_directory(sourceDir)) {
        cout << "Path exists" << "\n";
    } else {
        cout << "Path does not exist" << "\n";
        return 0;
    }

    char choice;
    for (recursive_directory_iterator it(sourceDir); it != end(it); it++) {
        if (it->is_directory()) {
            cout << "Include " << it->path().filename() << "? (y/n) <User> ";
            cin >> choice;
            if (choice != 'y') {
                cout << "Skipped " << it->path().filename() << "\n";
                it.disable_recursion_pending();
            } else {
                cout << "Included " << it->path().filename() << "\n";
            }
            continue;
        }
        entryList.push_back(*it);
    }
    cout << "\n";

    cout << "Files to be organized:" << "\n";
    for (const auto& entry: entryList) {
        if (entry.is_directory()) { continue; }
        cout << entry.path().filename() << "\n";
        extensions.insert(entry.path().extension());
    }
    cout << "\nWould you like to proceed? (y/n) <User> ";
    cin >> choice;
    if (choice != 'y') { return 0; }

    cout << "Extensions: " << "\n";
    for (const auto& ext: extensions) {
        cout << ext << "\n";
        create_directory(destinationDir / ext);
        extensionMap[ext] = destinationDir / ext;
    }
    cout << "\n";

    for (const auto& entry: entryList) {
        if (entry.is_directory()) { continue; }
        cout << "Moving " << entry.path() << " to " << extensionMap[entry.path().extension()] << "\n";
        rename(entry.path(), extensionMap[entry.path().extension()] / entry.path().filename());
    }
    cout << "\n";

    removeEmptyDir(sourceDir);

    return 0;
}