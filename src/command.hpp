#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <string>

using namespace std;

/*
 * This is a header file for the "command" class.
 * This file outlines all the parts of the command class.
 * While the code that actually implements the class can go here,
 * it generally goes in a separate '.cpp' file that shares the same name.
 */
 
/*
 * Each command should have two functions:
 * - One that takes no input, that generally should explain the command.
 * - One which does take input, and does something based on it.
 * There of course may be exceptions to the above.
 */
class command
{
public:
    command(string name, bool (*pntra)(), bool(*pntrb)(string));
    ~command();
    // Function with no input.
    bool (*runa)();
    // Function with input.
    bool (*runb)(string);
    // Name of the command, should be unique within the shell.
    string getname();
private:
    string name;
};

#endif // COMMAND_HPP
