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
        break 33               // set breakpoint at line 33
        run                    // run the program (until breakpoint)
        step                   // the next line (line 34) has been executed and is stored in memory. 
        p myMessage                   // print contents of the var myMessage.
        p &myMessage                  // prints the memory address of myMessage. 
        x/8tb <address of myMessage>  // print 8 successive bytes(b) in binary form(t) 

        output shown to screen: (binary form of "Courtney") 
        01000011   01101111   01110101   01110010   01110100   01101110   01100101   01111001 
    */
    vector<string> brothers{"David", "Ethan", "Adam"};
    for (string const& brother : brothers)
    {
        cout << "Hello " << brother << "!\n";
    }

    char myMessage[] = "Courtney";
    int number = 0;
    cout << "Please enter a number: ";
    
    cin >> number;
    cout << "Number entered: " << number; 



}