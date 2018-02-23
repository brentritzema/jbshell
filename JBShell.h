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
#include <queue>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

class JBShell {
public:
    JBShell();
    void run();
private:
    void execCommand(CommandLine);
    void waitForChild(CommandLine, int);
    Path mPath;
    Prompt mPrompt;
};

#endif
