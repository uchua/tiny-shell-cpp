#include "command.hpp"

/*
 * This is the implementation of the "command" class.
 * All the code that "actually does something" goes here.
 */
 
command::command(string name, bool (*pntra)(), bool(*pntrb)(string))
{
    this->name = name;
    this->runa = pntra;
    this->runb = pntrb;
}

command::~command()
{
}

string command::getname()
{
    return this->name;
}
