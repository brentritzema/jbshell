#include "Path.h"

Path::Path() {
    char* pPath = getenv("PATH");
    if (pPath!=NULL) {
        string sPath(pPath);
        string token;
        int i = 0;

        while (sPath.find(":", i) != string::npos) {
            token = sPath.substr(i, sPath.find(":", i) - i);
            mPath.push_back(token);
            i = sPath.find(":", i) + 1;
        }

        token = sPath.substr(i, sPath.find(":", i) - i);
        mPath.push_back(token);

        for (int x = 0; x != mPath.size(); ++x) {
            cout << mPath[x] << endl;
        }
    }
}
/* 
int Path::find(const string& program) const {
    return 0;
}

string Path::getDirectory(int i) const {
    return "";
}
*/
