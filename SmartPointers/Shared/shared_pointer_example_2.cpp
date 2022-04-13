#include <iostream>
#include <memory>

class MyClass
{
public:
    ~MyClass() { std::cout << "Destructor of MyClass called" << std::endl; }
};

int main()
{
	
	// If the resource which a shared pointer manages is no longer needed
	// in the current scope, the pointer can be "reset" to manage a 
	// different resource as illustrated below. 
	
    std::shared_ptr<MyClass> shared(new MyClass);
    std::cout << "shared pointer count = " << shared.use_count() << std::endl;

	// Simple Explanation: Basically "reset" calls the destructor to 
	// all shared pointers of the resource it's called on.
    shared.reset(new MyClass);
    std::cout << "shared pointer count = " << shared.use_count() << std::endl;

    return 0;
}