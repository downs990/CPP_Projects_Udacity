#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> mySharedPtr(new int);
    std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;


	// As can be seen from the output, neither of both weak pointers
	// increased the reference count. 
    std::weak_ptr<int> myWeakPtr1(mySharedPtr);
    std::weak_ptr<int> myWeakPtr2(myWeakPtr1);
    std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;

    std::weak_ptr<int> myWeakPtr3(new int); // COMPILE ERROR
 
	
	// Shown with myWeakPtr3, the attempt 
	// to directly create a weak pointer to an integer resource would
	// lead to a compile error.

    return 0;
}