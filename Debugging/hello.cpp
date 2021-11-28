#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::vector;
using std::string;

int main(){


    /*
    - How to run project?
         g++ -g hello.cpp      // notice -g argument for compiling process
         .\a.exe 

    - How to debug?
        gdb a
        list                   // to show the code
        break 31               // set breakpoint at line 31
        run                    // run the program (until breakpoint)
        step                   // the next line (line 32) has been executed and is stored in memory. 
        p number               // print contents of the var number.
    */
    vector<string> brothers{"David", "Ethan", "Adam"};
    for (string const& brother : brothers)
    {
        cout << "Hello " << brother << "!\n";
    }


    int number = 0;
    cout << "Please enter a number: ";
    
    cin >> number;
    cout << "Number entered: " << number; 



}