/*
 * CommandLine definitions for jbshell (which is just a shell)
 * Handles a single command line
 * Created by: Brent Ritzema for CS232
 * Calvin College Spring 2018
 */

#include "CommandLine.h"


CommandLine::CommandLine(istream &in) {

    mNoAmpersand = true;

    tuple <unsigned, char **> args = parseCommands(in);
    mArgc = get<0>(args);
    mArgv = get<1>(args);

}

tuple <unsigned, char **> CommandLine::parseCommands(istream &in) {

    vector <char *> commands;

    //parse argv
    string temp;

    while(in.peek() != '\n') {

        in >> temp;

        //convert from const char * to char *
        //adds null termination
        //dynamically allocates memory
        //http://en.cppreference.com/w/c/experimental/dynamic/strdup
        commands.push_back(strdup(temp.c_str()));

    }

    // Ignore the end of line
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    mNoAmpersand = ampersandCheck(commands);

    //length  + 1 because we need a null termination at the very end
    char ** argv = new char *[commands.size() + 1];

    //f we read anything, copy the commands from the vector to a char ** array
    if ( commands.size() > 0 ) {
        for (int i = 0; i < commands.size(); i++) {
            argv[i] = commands[i];
        }
    }

    //null terminate argv array
    argv[commands.size()] = NULL;

    return make_tuple(commands.size(), argv);
}

bool CommandLine::ampersandCheck(vector <char *> & commands) {
    //return true if the last element is &, false otherwise
    if(commands.size() != 0) {

        //fix comparison issue by converting to a string
        string command = commands.back();

        if(command != "&") {
            return true;
        } else {
            //must be an ampersand, remove it and return false
            commands.pop_back();
            return false;
        }
    } else {
        return false;
    }

}

char * CommandLine::getCommand() const {
    if(mArgc != 0)
        return this->getArgVector(0);
    else
        return NULL;
}

int CommandLine::getArgCount() const {
    return mArgc;
}

char ** CommandLine::getArgVector() const {
    if(mArgc != 0)
        return mArgv;
    else
        return NULL;
}

char * CommandLine::getArgVector(unsigned i) const {
    if(i < mArgc) {
        return mArgv[i];
    } else {
        cout << "Error: argument index out of range " << endl;
        return NULL;
    }
}

bool CommandLine::noAmpersand() const {
    return mNoAmpersand;
}

CommandLine::~CommandLine() {
    //cleanup each individual string
    for(int i = 0; i < mArgc; i++) {
        if(mArgv[i] != NULL)
            free(mArgv[i]);
    }

    //cleanup dynamic array if it exists
    if(mArgv != NULL) {
        delete [] mArgv;
    }
}
