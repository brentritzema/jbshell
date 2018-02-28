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
        pid_t pid;

        // taken partially from POGIL exercise
        if(commandLine.getArgCount() != 0) {

            /*fork child*/
            pid = fork();

            if (pid < 0) {
                //error occurred
                cerr << "Fork Failed" << endl;

            } else if (pid == 0) {
                if (mPath.getDirectory(mPath.find(commandLine.getCommand())) == "-1") {
                    cerr << "Program not found." << endl;
                    return;
                } else {
                    //child
                    execCommand(commandLine);
                }

            } else {
                //parent
                if (commandLine.noAmpersand()) {
                    waitForChild(pid);
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

void JBShell::waitForChild(int pid) {
    int status;

    //heavily relied on https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.bpxbd00/rtwaip.htm
    do {
        if((pid = waitpid(pid, &status, WUNTRACED)) == -1) {
            cerr << "wait() error" << endl;
        } else if (pid == 0) {
            //do nothing
        } else {
            if(WIFSTOPPED(status))
               cerr << "child exited unsuccessfully" << endl;
        }
    } while (pid == 0);
}
