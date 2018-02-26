/*
 * Shell file for jbshell (which is just a shell)
 * Created by: Brent Ritzema and Jesse Kuntz for CS232
 * Calvin College Spring 2018
 */

#include "JBShell.h"

JBShell::JBShell() {

}

void JBShell::run() {

    while(true) {
        cout << mPrompt.get() << flush;
        CommandLine commandLine(cin);

        // taken partially from POGIL exercise
        if(commandLine.getArgCount() != 0) {
            pid_t pid;

            /*fork child*/
            pid = fork();

            if (pid < 0) {
                //error occurred
                cerr << "Fork Failed" << endl;

            } else if (pid == 0) {
                execCommand(commandLine);

            } else {
                if (commandLine.noAmpersand()) {
                    waitForChild(commandLine, pid);
                }
                //if there is an amperstand, don't wait
            }
        }
    }

}

void JBShell::execCommand(CommandLine commandLine) {
    //fork worked 
    string command(commandLine.getCommand());
    string path = mPath.getDirectory(mPath.find(command)) + '/' + command;
    execve(path.c_str(), commandLine.getArgVector(), NULL);

    // if execv returns it failed
    cerr << "Exec of " << command << " failed" << endl;
}

void JBShell::waitForChild(CommandLine commandLine, int pid) {
    int status;

    //heavily relied on https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.bpxbd00/rtwaip.htm
    while(pid == 0) {
        if((pid = waitpid(pid, &status, WNOHANG)) == -1) {
            cerr << "wait() error" << endl;
        } else if (pid == 0) {
            //do nothing
        } else {
            if(!WIFEXITED(status))
               cerr << "child exited unsuccessfully" << endl; 
        }
    }
}
