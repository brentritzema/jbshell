/******************************************
 * Path.cpp contains the class and method
 * defintions of the Path class.
 *
 * Author: Jesse Kuntz
 * Date: ??
 * Class: CS 232
 * ****************************************/

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

// Constructor
Path::Path() {
    char* pPath = getenv("PATH");
    if (pPath != NULL) {
        string sPath(pPath);
        populateVPath(sPath);
    } else {
        cout << "Nothing in PATH." << endl;
    }

}

// find() searches through all of the directories in
// vPath until it finds the program, and returns the
// index of the directory that it was found in. Uses
// searchDir, defined at the bottom of this file.
int Path::find(const string& program) const {
    int index = -1;
    for (int i = 0; i < vPath.size(); i++) {
        index = searchDir(i, program);
        if (index != -1) break;
    }
    return index;
}

// getDirectory() returns the name of the
// directory in vPath specified by the given
// index.
string Path::getDirectory(int i) const {
    if (i == -1) {
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

    // Splits up all of the elements of PATH and
    // puts them into vPath.
    while (s.find(":", i) != string::npos) {
        token = s.substr(i, s.find(":", i) - i);
        vPath.push_back(token);
        i = s.find(":", i) + 1;
    }

    // Puts the last directory into vPath, separated
    // because there is no ':' at the end of PATH.
    token = s.substr(i, s.find(":", i) - i);
    vPath.push_back(token);
}

// Helper method for find(), to keep the member method nice and clean!
int Path::searchDir(int i, const string& progName) const {
    // The following is based off of the code found at: http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fo%2Fopendir.html
    DIR* dirp;
    struct dirent* direntp;

    dirp = opendir(vPath[i].c_str());
    if (dirp != NULL) {
        for(;;) {
            direntp = readdir(dirp);
            if(direntp != NULL) {
                if(direntp->d_name == progName) {
                    return i;
                }
            } else {
                break;
            }
        }
        closedir(dirp);
    }
    return -1;
}

// for testing the above method:
// cout << direntp->d_name << endl;
// perror(vPath[i].c_str());
// cout << vPath[index] << endl;
