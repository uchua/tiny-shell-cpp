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
/*
 * Below is the "public" tag. This tells the compiler that all parts of the class
 * under this tag can be accessed by any other code. This means that any functions
 * here can be called anywhere by any other code, and any variables here can be
 * changed anywhere and by any code.
 */
public:
    command(string name, bool (*pntra)(), bool(*pntrb)(string));
    ~command();
    // Function with no input.
    bool (*runa)();
    // Function with input.
    bool (*runb)(string);
    // Name of the command, should be unique within the shell.
    string getname();
/*
 * Below is the "private" tag. This tells the compiler that all parts of the class
 * under this tag should only be accessible by functions within the class itself.
 * This way no outside code can call functions or access/change variables.
 */
private:
    string name;
};

#endif // COMMAND_HPP
