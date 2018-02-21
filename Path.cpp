#include "Path.h"

/******************************************
 * Necessary methods, as defined by the 
 * assignment.
 * ****************************************/

Path::Path() {
    char* pPath = getenv("PATH");
    if (pPath!=NULL) {
        string sPath(pPath);
        populateVPath(sPath);

        printVPath(vPath);
    }
}

int Path::find(const string& program) const {
    int index = -1;
    for (int i = 0; i < vPath.size(); i++) {
        if (vPath[i].find(program) != string::npos) index = i;
    }
    cout << index;
    return index;
}

string Path::getDirectory(int i) const {
    return vPath[i];
}


/******************************************
 * Methods to help keep things clean 
 * and readable.
 * ****************************************/

// Helper method for debugging
void Path::printVPath(vector<string> v) {
    for (int x = 0; x != v.size(); ++x) {
        cout << v[x] << endl;
    }
}

// Guts of the contructor, populates vPath with what is in PATH
void Path::populateVPath(string s) {
    string token;
    int i = 0;

    while (s.find(":", i) != string::npos) {
        token = s.substr(i, s.find(":", i) - i);
        vPath.push_back(token);
        i = s.find(":", i) + 1;
    }

    token = s.substr(i, s.find(":", i) - i);
    vPath.push_back(token);
}

