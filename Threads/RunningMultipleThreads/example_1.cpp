#include <iostream>
#include <thread>
#include <vector>

void printHello()
{
    // perform work
    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << std::endl;
}

int main()
{

    /*
        When we try to compile the program using the push_back() function (which is the usual 
        way in most cases), we get a compiler error. The problem with our code is that by pushing 
        the thread object into the vector, we attempt to make a copy of it. However, thread 
        objects do not have a copy constructor and thus can not be duplicated. If this were 
        possible, we would create yet another branch in the flow of execution - which is not what
        we want. The solution to this problem is to use move semantics, which provide a convenient 
        way for the contents of objects to be 'moved' 
        between objects, rather than copied.
    */


    // create threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 5; ++i)
    {
        // copying thread objects causes a compile error
        /*
        std::thread t(printHello);
        threads.push_back(t);                                    // Uses copy. (pass by value)
        */

        // moving thread objects will work
        threads.emplace_back(std::thread(printHello));           // Uses move semantics  (pass by reference)
    }

    // do something in main()
    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    // call join on all thread objects using a range-based loop
    for (auto &t : threads)
        t.join();

    return 0;
}
