/*
 * Shell file for jbshell (which is just a shell)
 * Created by: Brent Ritzema and Jesse Kuntz for CS232
 * Calvin College Spring 2018
 */

#include "JBShell.h"

/******************************************
 * Necessary methods, as defined by the
 * assignment.
 * ****************************************/

JBShell::JBShell() {

}

void JBShell::run() {

    while(true) {
        cout << mPrompt.get() << flush;
        CommandLine commandLine(cin);

        // taken partially from POGIL exercise
        if(commandLine.getArgCount() != 0) {

            string command = commandLine.getCommand();

            if(command == "cd") {
                changeWorkingDirectory(commandLine);
            } else if (command == "pwd") {
                printWorkingDirectory(commandLine);
            } else if (command == "exit") {
                break;
            } else {
                // not a "built-in" command, so search the PATH
                forkChild(commandLine);
            }
        }
    }
}

/******************************************
 * Methods to help keep things clean
 * and readable.
 * ****************************************/

void JBShell::printWorkingDirectory(const CommandLine &commandLine) {
    string cwd = mPrompt.getCWD();
    if(commandLine.getArgCount() != 1) {
        cerr << "incorrect number of arguments passed to pwd" << endl;
    } else {
        if (cwd == "") {
            cerr << "failed to fetch current working directory" << endl;
        } else {
            cout << cwd << endl;
        }
    }
}

void JBShell::changeWorkingDirectory(const CommandLine &commandLine) {
    if(commandLine.getArgCount() != 2) {
        cerr << "incorrect number of arguments to cd" << endl;
    } else {
        string newPath = commandLine.getArgVector(1);
        if(chdir(newPath.c_str()) == -1) {
            perror("cd failed");
        } else {
            // success
            // update prompt by reinitializing
            mPrompt = Prompt();
        }
    }
}

// Method for forking a child, including support for the '&' option
void JBShell::forkChild(const CommandLine &commandLine) {
    pid_t pid;

    /* fork child */
    pid = fork();

    if (pid < 0) {
        // error occurred
        cerr << "Fork Failed" << endl;

    } else if (pid == 0) {
        if (mPath.getDirectory(mPath.find(commandLine.getCommand())) == "-1") {
            cerr << "Program not found." << endl;
            return;
        } else {
            // child
            execCommand(commandLine);
        }

    } else {
        // parent
        if (commandLine.noAmpersand()) {
            waitForChild(pid);
        }
        // IF there is an ampersand, don't wait
    }
}

void JBShell::execCommand(const CommandLine &commandLine) {
    // fork worked
    string command(commandLine.getCommand());
    string path = mPath.getDirectory(mPath.find(command)) + '/' + command;
    execve(path.c_str(), commandLine.getArgVector(), NULL);

    // if execv returns it failed
    cerr << "Exec of " << command << " failed" << endl;
}

void JBShell::waitForChild(int pid) {
    int status;

    // heavily relied on https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.bpxbd00/rtwaip.htm
    do {
        if((pid = waitpid(pid, &status, WUNTRACED)) == -1) {
            cerr << "wait() error" << endl;
        } else if (pid == 0) {
            // do nothing
        } else {
            if(WIFSTOPPED(status))
               cerr << "child exited unsuccessfully" << endl;
        }
    } while (pid == 0);
}
