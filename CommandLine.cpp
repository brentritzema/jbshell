/*
 * CommandLine definitions for jbshell (which is just a shell)
 * Handles a single command line
 * Created by: Brent Ritzema and Jesse Kuntz for CS232
 * Calvin College Spring 2018
 */

#include "CommandLine.h"


CommandLine::CommandLine(istream &in) {
    
    tuple <unsigned, char **> args = parseCommands(in);
    mArgc = get<0>(args);
    mArgv = get<1>(args);
}

tuple <unsigned, char **> CommandLine::parseCommands(istream &in) {

    //max command length of 1024
    char ** argv = new char *[1024];
    unsigned argc = 0;

    //parse argv
    string temp;

    while(in.peek() != '\n') {
        
        in >> temp;
        //convert from const char * to char *
        //http://en.cppreference.com/w/c/experimental/dynamic/strdup
        argv[argc] = strdup(temp.c_str());
        argc++;
        if (argc >= 1023) {
            cout << "Error: Too many arguments in command" << endl;
            break;
        }
    }

    //if we read in anything, make argc = argc + 1 (because that's its size)
    //else do nothing
    if ( argc > 0 )
        argc++;

    return make_tuple(argc, argv);
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
    //return true if the last element is &, false otherwise
    if(mArgc != 0)
        return mArgv[mArgc-1] != "&" ? true : false;
    else
        return false;
}

CommandLine::~CommandLine() {
    //cleanup each individual string
    for(int i = 0; i < mArgc; i++) {
        free(mArgv[i]);
    }

    //cleanup dynamic array if it exists
    if(mArgv != NULL) {
        delete [] mArgv;
    }
}
