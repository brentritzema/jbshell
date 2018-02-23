/******************************************
 * Prompt.cpp contains the class and method
 * defintions of the Prompt class.
 *
 * Author: Jesse Kuntz
 * Date: ??
 * Class: CS 232
 * ****************************************/

#include "Prompt.h"

/******************************************
 * Necessary methods, as defined by the
 * assignment.
 * ****************************************/

Prompt::Prompt() {
    // Allocate the buffer size.
    char cwd[256];

    // Check, so there is no buffer overflow.
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Hostname
        char hostname[HOST_NAME_MAX];
        gethostname(hostname, HOST_NAME_MAX);

        // Username
        char username[LOGIN_NAME_MAX];
        getlogin_r(username, LOGIN_NAME_MAX);

        mPrompt = string(username) + "@" + string(hostname) + ":" + cwd + "$ ";
    } else {
        cout << "cwd too big!" << endl;
    }
}

// Accessor.
string Prompt::get() const {
    return mPrompt;
}