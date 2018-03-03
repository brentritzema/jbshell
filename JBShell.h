/*
 * Shell file for jbshell (which is just a shell)
 * Created by: Brent Ritzema and Jesse Kuntz for CS232
 * Calvin College Spring 2018
 */

#ifndef JBSHELL_H
#define JBSHELL_H

#include "CommandLine.h"
#include "Path.h"
#include "Prompt.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

class JBShell {
public:
    JBShell();
    void run();
private:
    //print the working directory
    void printWorkingDirectory(const CommandLine &);

    //change working directory
    void changeWorkingDirectory(const CommandLine &);

    //forks child, child executes while parent waits
    void forkChild(const CommandLine &);

    //child executes command
    void execCommand(const CommandLine &);

    //parent waits
    void waitForChild(int);

    Path mPath;
    Prompt mPrompt;
};

#endif
