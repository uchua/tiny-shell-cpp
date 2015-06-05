#include "command.hpp"

/*
 * This is the implementation of the "command" class.
 * All the code that "actually does something" goes here.
 */
 
command::command(string name, bool (*pntra)(), bool(*pntrb)(string))
{
    /*
     * This is the constructor. As the name suggests it "constructs" a new
     * instance of the command class to be used in code.
     */
    this->name = name;
    this->runa = pntra;
    this->runb = pntrb;
}

command::~command()
{
    /*
     * This is a destructor. It is called when an instance of a class is no longer
     * needed and is going to be removed from memory.
     */
}

string command::getname()
{
    /*
     * This is known as a "Getter" or "Accessor" function.
     * It allows you to retrieve the value of a variable without
     * giving the code the ability to alter it.
     */
    return this->name;
}
