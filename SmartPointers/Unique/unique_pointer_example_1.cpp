// 		As can be seen, a smart pointer is a class template that is declared 
// on the stack and then initialized by a raw pointer (returned by new ) 
// to a heap-allocated object. The smart pointer is now responsible for 
// deleting the memory that the raw pointer specifies - which happens 
// as soon as the smart pointer goes out of scope. Note that smart pointers 
// always need to be declared on the stack, otherwise the scoping 
// mechanism would not work.

#include <memory>

void RawPointer()
{
    int *raw = new int; // create a raw pointer on the heap
    *raw = 1; // assign a value
    delete raw; // delete the resource again
}

void UniquePointer()
{
    std::unique_ptr<int> unique(new int); // create a unique pointer on the stack
    *unique = 2; // assign a value
    // delete is not neccessary
}


