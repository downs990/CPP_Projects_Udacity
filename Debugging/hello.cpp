#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;

int main(){

    std::vector<std::string> brothers{"David", "Ethan", "Adam"};


    

    for (std::string const& brother : brothers)
    {
        cout << "Hello " << brother << "!\n";
       
    }


    int number = 0;
    cout << "Please enter a number: ";
    
    cin >> number;
    cout << "Number entered: " << number; 



}