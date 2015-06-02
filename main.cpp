#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include "src/tools.hpp"
#include "src/commands.hpp"
#ifndef GetCurrentDir
    #ifdef _WIN32
        #include <direct.h>
        #define GetCurrentDir _getcwd
    #else
        #include <unistd.h>
        #define GetCurrentDir getcwd
    #endif
#endif

using namespace std;

/*
 * ABOVE:
 * "#include" lines tell the compiler to include code found in those files.
 * "iostream" and "string" are part of the standard c++ code. 
 * "tools.hpp" and "commands.hpp" are other source code files.
 * The "#ifndef", "#ifdef", "#else", "#endif" sequence above is a macro for the compiler.
 * This macro, like the "#include" macros, tells the compiler to do something.
 * In this case, it tells the compiler to define "GetCurrentDir" based on whether
 * or not this program is being compiled for Windows.
 * 
 * "using namespace std;" tells the compiler that when looking for things (e.g. string, cout, cin, etc.),
 * that it should first look in the std namespace, which more or less means the c++ standard files.
 */

/*
 * BELOW:
 * Good coding etiquette is to capitalize the names of global and static variables.
 * TERMINATOR - what is to be displayed at the end of the input line ('>' in cmd.exe, usually '$' or '#' in linux)
 * CONTINUE - tells the program whether or not it should keep running, kind of like a kill switch
 * COMMANDS - a map of strings to commands, used to handle user input
 *          - see http://www.cplusplus.com/reference/map/map/ for more information on the c++ map class
 * MAX_LINE_LENGTH - maximum length for a single line of input to the shell
 */
static string TERMINATOR = "> ";
bool CONTINUE = true;
map<string, command> COMMANDS;
static int MAX_LINE_LENGTH = 1000;

bool iscommand(string cmd)
{
    // Checks if the given string maps to a command
    if (COMMANDS.count(cmd) < 1) {
        return false;
    }
    else {
        return true;
    }
}

bool execute(string c)
{
    /*
     * Checks and executes commands in X steps:
     * - Divides the string into two parts at a space
     * - Checks if the command is to exit the shell
     * - Then checks if the input is even a command
     * - If either are the above are true returns true
     * - Otherwise returns false, indicating unrecognized input
     */
    string cmd = bfrspc(c); // Separate string at space
    if (cmd == "exit") { // Check if command is to exit
        CONTINUE = false;
        return true;
    }
    else if (iscommand(cmd)) { // Check if input is even a commmand
        string args = aftspc(c); // Separate arguements from command
        if (args.length() > 0) { 
            COMMANDS.find(cmd)->second.runb(args);
        }
        else {
            COMMANDS.find(cmd)->second.runa();
        }
        return true;
    }
    else {
        return false;
    }
}

pair<string, command> cmdpair(command cmd)
{
    // Creates a string-command pair which can be placed into the COMMANDS map
    return pair<string, command>(cmd.getname(),cmd);
}

void load()
{
    // Load variables into the shell
    char currpath[FILENAME_MAX];
    GetCurrentDir(currpath,sizeof(currpath));
    ACTIVE_DIR = string(currpath);
    // Load all desired commands into the shell
    COMMANDS.insert(cmdpair(echo));
    COMMANDS.insert(cmdpair(ls));
    COMMANDS.insert(cmdpair(list));
}

void mainloop(string )
{
    /*
     * You don't want to have to keep relaunching the shell for each command, right?
     * So you use a simple loop with a boolean (true/false), flag to keep it running.
     * Below you see the code for the main loop in the shell, as long as the shell is
     * told to continue, it keeps looping.
     * Each loop does the follow:
     * - Prints the current directory to the terminal, followed by the terminator.
     * - Takes a line of input from the terminal up to the given maximum length.
     * - Then attempts to execute that line of input as a command.
     * - As long as the shell is set to continue, starts the process again.
     */
    char input[MAX_LINE_LENGTH];
    while (CONTINUE) {
        print(ACTIVE_DIR);
        print(TERMINATOR);
        cin.getline(input,MAX_LINE_LENGTH);
        if (!execute(string(input))) {
            printer("Unrecognized command!");
        }
    }
}

/*
 * Below is the main function.
 * The main function of the main.cpp file is the first thing executed
 * when the compiled program is ran. Everything starts here.
 */
int main(int argc, string argv)
{
    /*
     * Start up the shell in a few steps:
     * - Load all the desired commands/variables.
     * - Print a welcome message if desired.
     * - Begin the main loop of the shell.
     */
    load();
	printer("Welcome to Tiny Shell!");
    mainloop(argv);
	return 0;
}
