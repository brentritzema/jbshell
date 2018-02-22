#include "Path.h"

/******************************************
 * To figure out as a pair:
 * - Do I need to send any error handling?
 * Or should I be printing it?
 * - opendir() error handling
 * - getDirectory() error handling
 * - Path() error handling
 * - Right now it avoids all errors, just doesn't
 * handle them.
 * ****************************************/

/******************************************
 * Necessary methods, as defined by the
 * assignment.
 * ****************************************/

Path::Path() {
    char* pPath = getenv("PATH");
    if (pPath!=NULL) {
        string sPath(pPath);
        populateVPath(sPath);

        // FOR TESTING
        //  printVPath(vPath);
    }
    // Do something if the PATH IS Null?
}

int Path::find(const string& program) const {
    int index = -1;
    for (int i = 0; i < vPath.size(); i++) {
        // The following is based off of the code found at:
        // http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fo%2Fopendir.html
        DIR* dirp;
        struct dirent* direntp;

        dirp = opendir(vPath[i].c_str());
        if (dirp != NULL) {
            for(;;) {
                direntp = readdir(dirp);
                if(direntp == NULL) break;
                if(direntp->d_name == program) {
                    index = i;
                    break;
                }
                // FOR TESTING
                // cout << direntp->d_name << endl;
            }
            closedir(dirp);
        } else {
            // FOR TESTING
            // I mean... don't really need to print this.
            // perror(vPath[i].c_str());
        }
    }
    // FOR TESTING
    // cout << index << endl;
    // cout << vPath[index] << endl;
    return index;
}

string Path::getDirectory(int i) const {
    if (i > vPath.size() || i < 0) {
        cout << "Index out of bounds." << endl;
        // What do I return here?
        return "-1";
    } else {
        return vPath[i];
    }
}


/******************************************
 * Methods to help keep things clean
 * and readable.
 * ****************************************/

// Helper method for debugging
void Path::printVPath(vector<string> v) {
    for (int i = 0; i != v.size(); ++i) {
        cout << i << ". " << v[i] << endl;
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



