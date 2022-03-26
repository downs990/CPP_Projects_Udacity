#include <iostream>



// What is ExclusiveCopy ? 
// Whenever a resource management object is copied, the resource handle is transferred from the
// source pointer to the destination pointer. The source pointer is set to nullptr to make
// ownership exclusive. At any time, the resource handle belongs only to a single object, which
// is responsible for its deletion when it is no longer needed.
class ExclusiveCopy
{
private:
    int *_myInt;

public:
    ExclusiveCopy()
    {
        _myInt = (int *)malloc(sizeof(int));
        std::cout << "resource allocated" << std::endl;
    }
    ~ExclusiveCopy()
    {
		// This prevents a double deletion error. It will only be deleted if 
		// it has Not alreaady been deleted. 
        if (_myInt != nullptr)
        {
            free(_myInt);
            std::cout << "resource freed" << std::endl;
        }
            
    }
    ExclusiveCopy(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr; // Prevents 2 variables (handles )from having access to the same memory in the heap.
		
		
		
		// One problem in this implementation is that for a short time there are effectively
		// two valid handles to the same resource - after the handle has been copied and before 
		// it is set to nullptr. In concurrent programs, this would cause a data race for the resource. 
		//A much better alternative to handle exclusive ownership in C++ would be to use "move semantics".
    }
    ExclusiveCopy &operator=(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
        return *this;
    }
};

int main()
{
    ExclusiveCopy source;
    ExclusiveCopy destination(source);

    return 0;
}