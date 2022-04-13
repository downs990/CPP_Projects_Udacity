#include <iostream>
#include <memory>

int main()
{
	
	//  We can access the internal reference count by using the method
	// .use_count(). 
	
	// In the inner block, a second shared pointer shared2
	// is created and shared1 is assigned to it. In the copy constructor of
	// shared_ptr, the internal resource pointer is copied to shared2 
	// and the resource counter is incremented in both shared1 and shared2
	
    std::shared_ptr<int> shared1(new int);
    std::cout << "shared pointer count = " << shared1.use_count() 
			  << std::endl;


    {
        std::shared_ptr<int> shared2 = shared1;
        std::cout << "shared pointer count = " << shared1.use_count() 
			      << std::endl;
    }
	
	// The lifetime of "shared2" is limited to the scope denoted by 
	// the enclosing curly brackets. Thus, once this scope is left and 
	// "shared2" is destroyed, the reference counter in shared1 is decremented -
	// which is shown in the output when you run this code. 
    
    std::cout << "shared pointer count = " << shared1.use_count() 
		      << std::endl;

    return 0;
}