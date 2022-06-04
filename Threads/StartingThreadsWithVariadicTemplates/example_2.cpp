#include <iostream>
#include <thread>
#include <string>

void printName(std::string name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    std::cout << "Name (from Thread) = " << name << std::endl;
}

int main()
{
    std::string name1 = "MyThread1";
    std::string name2 = "MyThread2";


    std::thread t1(printName, name1, 50); // name1 is "copy by value" 
    std::thread t2(printName, std::move(name2), 100); // name2 is passed using "move semantics"

    // wait for threads before returning
    t1.join();
    t2.join();

    // print name from main
    std::cout << "Name (from Main) = " << name1 << std::endl;
    std::cout << "Name (from Main) = " << name2 << std::endl; // name2 is empty now because it was moved to printName() using move semantics

    return 0;
}