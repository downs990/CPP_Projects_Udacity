#include <iostream>
#include <memory>

int main()
{
    // As we have seen with raw pointers, you can never be sure wether the memory 
    // resource to which the pointer refers is still valid. With a weak pointer, even 
    // though this type does not prevent an object from being deleted, the validity
    // of its resource can be checked. The code on the right illustrates how to 
    // use the expired() function to do this.
        
    std::shared_ptr<int> mySharedPtr(new int);
    std::weak_ptr<int> myWeakPtr(mySharedPtr);

    mySharedPtr.reset(new int);

    if (myWeakPtr.expired() == true)
    {
        std::cout << "Weak pointer expired!" << std::endl;
    }

    return 0;
}