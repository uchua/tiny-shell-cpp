#ifndef TOOLS_HPP
#define TOOLS_HPP
#include <iostream>

using namespace std;

void printer(string s)
{
    /* 
     * "cout" is the terminal using "cout << s;" prints the string s to the terminal
     * "cout << endl;" tells the terminal to move down to the next line
     * Combining the two into "cout << s << endl;" prints the string s to the terminal and moves to a new line
     */ 
    cout << s << endl;
}

void print(string s)
{
    /*
     * Prints a string to the terminal like above, but without the new line.
     */
    cout << s;
}

string bfrspc(string s)
{
    // Returns the string up to the first space
    unsigned int i = 0;
    const char* cs = s.c_str();
    while (cs[i] != ' ' && i < s.length()) {
        i++;
    }
    return s.substr(0,i);
}

string aftspc(string s)
{
    // Returns the string after the first space
    unsigned int i = 0;
    const char* cs = s.c_str();
    while (cs[i] != ' ' && i < s.length()) {
        i++;
    }
    if (i >= s.length()) {
        return "";
    }
    else {
        return s.substr(i+1,s.length()-i);
    }
}

#endif // TOOLS_HPP