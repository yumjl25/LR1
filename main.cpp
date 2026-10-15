#include <iostream>
#include <cstring>
#include "storage.h"

using namespace std;

int main(int argc, char** argv) {
    const char* filename = nullptr;
    const char* query = nullptr;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (!filename || !query) {
        cout << "Usage: " << argv[0]
             << " --file <file> --query '<command>'" << endl;
        return 1;
    }

    Storage* s = storageCreate();
    storageLoad(s, filename);

    storageExecute(s, query, false);

    storageSave(s, filename);
    storageFree(s);
    return 0;
}