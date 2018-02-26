/*
 * CommandLine declarations for jbshell (which is just a shell)
 * Handles a single command line
 * Created by: Brent Ritzema and Jesse Kuntz for CS232
 * Calvin College Spring 2018
 */

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <tuple>
#include <limits>
#include <vector>

using namespace std;

class CommandLine {
public:
    /*
     * Constructs a CommandLine by reading a line of a command from in,
     * parsing it, and building sintacen variables for argc and argv.
     *
     * @param: istream &in, an input stream for the command line
     * @return: none
     */
    CommandLine(istream &in);

    /*
     * Returns a pointer to the command portion of the command line
     *
     * @param: none
     * @return: char pointer to command
     */ 
    char * getCommand() const;

    /*
     * Returns the number of arguments (aka argc)
     *
     * @param: none
     * @return: number of arguments (argc)
     */ 
    int getArgCount() const;

    /*
     * Returns a pointer to a char* array (aka argv)
     *
     * @param: none
     * @return: char pointer to array of commands (argv)
     */ 
    char ** getArgVector() const;

    /*
     * Returns a char* command (aka argv[i])
     *
     * @param: int i, the position of the command in the argv array 
     * @return: char pointer to ith command (argv[i])
     */ 
    char * getArgVector(unsigned i) const;

    /*
     * Returns whether or not an amperstand was given to the command line
     *
     * @param: none
     * @return: true if and only if no amperstand was given to the command line
     */ 
    bool noAmpersand() const;

    /*
     * Cleans up argv
     *
     * @param: none
     * @return: none
     */ 
    virtual ~CommandLine();

private:
    /*
     * Parses commands from stream and load into (argc, argv)
     *
     * @param: istream &in, input stream
     * @return: a tuple with argc and argv 
     */ 
    tuple <unsigned, char **> parseCommands(istream &in);

    char ** mArgv;
    unsigned mArgc;
};

#endif
