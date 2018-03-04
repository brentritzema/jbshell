/******************************************
 * Prompt.h contains the class and method
 * declarations of the Prompt class.
 *
 * Author: Jesse Kuntz
 * Class: CS 232
 * ****************************************/

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>

#include <limits.h>

using namespace std;

class Prompt {
    private:
        string mPrompt;
        string mCWD;
    public:
        Prompt();

        // Returns full prompt string
        string get() const;

        // Returns current working directory
        string getCWD() const;
};
