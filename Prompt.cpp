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
        mPrompt = cwd;
    } else {
        // Print an error?
    }
}

// Accessor.
string Prompt::get() const {
    return mPrompt + "/$ ";
}