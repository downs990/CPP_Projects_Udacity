#include <iostream>
#include <memory>

int main()
{
    // construct a unique pointer
    std::unique_ptr<int> uniquePtr(new int);
    
    // (1) shared pointer from unique pointer
	
	// You can see that this can be achieved by using std::move,
	// which calls the move assignment operator on sharedPtr1 and 
	// steals the resource from uniquePtr while at the same time 
	// invalidating its resource handle on the heap-allocated integer.
    std::shared_ptr<int> sharedPtr1 = std::move(uniquePtr);
	

    // (2) shared pointer from weak pointer
	
	// Imagine that you have been passed a weak pointer to a memory
	// object which you want to work on. To avoid invalid memory 
	// access, you want to make sure that the object will not be 
	// deallocated before your work on it has been finished. To do
	// this, you can convert a weak pointer to a shared pointer by 
	// calling the lock() function on the weak pointer.
    std::weak_ptr<int> weakPtr(sharedPtr1);
    std::shared_ptr<int> sharedPtr2 = weakPtr.lock();
	

    // (3) raw pointer from shared (or unique) pointer   
	
	// This operation does not decrease the reference count within
	// sharedPtr2. This means that calling delete on rawPtr in the 
	// last line before main returns will generate a runtime error as 
	// a resource is trying to be deleted which is managed by 
	// sharedPtr2 and has already been removed. 
 
    int *rawPtr = sharedPtr2.get();
    delete rawPtr;


	
	// The output of the program when compiled with g++ thus is:
	//	 malloc: *** error for object 0x1003001f0: 
	//	 pointer being freed was not allocated
    return 0;
}