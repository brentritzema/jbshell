#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <dirent.h>

using namespace std;

class Path {
    private:
        vector<string> vPath;
        void printVPath(vector<string> v);
        void populateVPath(string s);
    public:
        Path();
        int find(const string& program) const;
        string getDirectory(int i) const;
};