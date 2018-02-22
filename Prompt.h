/******************************************
 * Prompt.h contains the class and method
 * declarations of the Prompt class.
 *
 * Author: Jesse Kuntz
 * Date: ??
 * Class: CS 232
 * ****************************************/

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>

using namespace std;

class Prompt {
    private:
        string mPrompt;
    public:
        Prompt();
        string get() const;
};