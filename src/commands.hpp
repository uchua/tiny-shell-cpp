#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <string>
#include "tools.hpp"
#include "command.hpp"
#ifdef _WIN32
    #include <windows.h>
#else
    #include <dirent.h>
#endif

using namespace std;

// Global variable for the current directory
string ACTIVE_DIR = "";

/*
 * This file will contain all the defined commands for the shell.
 * Just to keep all the files as neat as possible.
 */

bool echoa()
{
    // Commands with no arguements should explain the command.
    printer("echo: Prints a string to the terminal.");
    return true;
}

bool echob(string s)
{
    /*
     * Commands with arguements should do something based on them.
     * For example, this echo command prints the given string to the terminal.
     */
    printer(s);
    return true;
}

command echo = command("echo", &echoa, &echob);

bool lsa()
{
    /*
     * Working with file systems in C++ is very tricky.
     * It (almost) always requires some kind of outside library.
     * Below you'll see the code required to list the contents of a directory.
     * Note that most of the below code is actually written in C not C++.
     */
    #ifdef _WIN32
    /*
     * The above tells the compiler to check if _WIN32 is defined.
     * This indicates (at compile time) that the computer is running Windows.
     * - Note that despite the name _WIN32 is defined on 32 and 64 bit Windows Operating Systems.
     * Below is the code needed to output the contents of a directory in Windows.
     */
    HANDLE hFind;
    WIN32_FIND_DATA file;
    hFind = FindFirstFile((ACTIVE_DIR+"\\*").c_str(),&file); // Finds first file in the given directory
    if (hFind != INVALID_HANDLE_VALUE) { // If the file isn't invalid continue
        string filename;
        while (FindNextFile(hFind,&file)) { // While there are more files
            filename = file.cFileName;      // get their names as char arrays
            cout << filename << endl;       // and print them to the terminal
        }
        FindClose(hFind);
    }
    #else
    /*
     * If _WIN32 is not defined, the system is not running Windows.
     * Therefor, you'll need to use a different method to access the filesystem.
     * In this case, dirent.h is used.
     */
    DIR *d;
    struct dirent *dir;
    d = opendir(ACTIVE_DIR.c_str()); // Open the directory
    if (d != NULL) { // Makes sure the directory exists before continuing
        while ((dir = readdir(d)) != NULL) { // While there are more files in the directory
            cout << dir->d_name << endl;     // write their names to the terminal
        }
        closedir(d); // Close the directory
    }
    #endif
}

bool lsb(string s)
{
    // Calling ls with arguments simply ignores the arguments
    return lsa();
}

/*
 * When you build your own shell you can do stupid stuff to annoy/help people,
 * such as making aliases for commands as shown below. Despite "ls" and "list"
 * being separate commands, they do the exact same thing.
 */ 
command ls = command ("ls", &lsa, &lsb);
command list = command ("list", &lsa, &lsb);

bool cda()
{
    // The cd, or current directory, command prints ACTIVE_DIR to the terminal.
    printer(ACTIVE_DIR);
    return true;
}

bool cdb(string s)
{
    // When given arguements, the cd command changes the current directory
    #ifdef _WIN32
    /*
     * Reusing some code from the ls command, you can check if a given directroy exists.
     * If it does, you can then simply change the ACTIVE_DIR variable to that directory
     * so all further commands run on that directory.
     * - Note that, for the current implementation, a full path is required
     */
    HANDLE hFind;
    WIN32_FIND_DATA file;
    hFind = FindFirstFile(s.c_str(),&file); // Finds first file in the given directory
    if (hFind != INVALID_HANDLE_VALUE) { // If the file isn't invalid continue
        ACTIVE_DIR = s;
        FindClose(hFind);
    }
    #else
    DIR *d;
    struct dirent *dir;
    d = opendir(s.c_str()); // Open the directory
    if (d != NULL) { // Makes sure the directory exists before continuing
        ACTIVE_DIR = s;
        closedir(d); // Close the directory
    }
    #endif
}

command cd = command ("cd", &cda, &cdb);

#endif // COMMANDS_HPP