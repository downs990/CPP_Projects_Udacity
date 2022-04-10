
// RAII memory management class
class MyInt
{
    int *_p; // pointer to heap data
	
	
public:

	// Constructor takes a pointer to a memory resource. 
    MyInt(int *p = NULL) { _p = p; }
	
	// When the destructor is called, the resource is deleted from memory -
	//	which makes MyInt class an RAII managment class. 
    ~MyInt() 
    { 
        std::cout << "resource " << *_p << " deallocated" << std::endl;
        delete _p; 
    }
	
	// overloading the dereferencing operator allows us to dereference MyInt 
	//  objects in the same way as with raw pointers. 
    int &operator*() { return *_p; } 
};


int main()
{
    double den[] = {1.0, 2.0, 3.0, 4.0, 5.0}; // created on the stack 
    for (size_t i = 0; i < 5; ++i)
    {
		// Example 1: RAW POINTER 
		
				// allocate the resource on the heap
				// double *en = new double(i);

				// use the resource
				//std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;

				// deallocate the resource
				//delete en;
				
		// Example 2: RAII 
		
				// allocate the resource on the stack (which, internally, created an integer on the heap using "new")
				MyInt en(new int(i));

				// use the resource
				std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;
    
	
				// NOTE: Because the MyInt object en lives on the stack, it 
				//      is automatically deallocated after each loop cycle - which calls 
				//      the destructor to release the heap memory. 
	
	}
    }

    return 0;
}