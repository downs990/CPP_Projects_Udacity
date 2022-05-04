#include <stdlib.h>
#include <iostream>

class MyMovableClass
{
private:
    int _size;
    int *_data;

public:

	// 1 : destructor
    ~MyMovableClass()                                           
    {
        std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
        delete[] _data;
    }
	
    MyMovableClass(size_t size) 
    {
        _size = size;
        _data = new int[_size];
        std::cout << "CREATING instance of MyMovableClass at " << this
                  << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
    }
    
	// 2 : copy constructor
    MyMovableClass(const MyMovableClass &source)             
    {
        _size = source._size;
        _data = new int[_size];
        *_data = *source._data;
        std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
    }

    // 3 : copy assignment operator
    MyMovableClass& operator=(const MyMovableClass &source)    
    {
        std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
        
        // Protects against self assignment. 
        if (this == &source)
            return *this;

        delete[] _data;
        _data = new int[source._size];
        *_data = *source._data;
        _size = source._size;
        return *this;
    }
	
	
	// 4 : move constructor
	MyMovableClass(MyMovableClass &&source)  
    {
        std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
        _data = source._data;
        _size = source._size;
        source._data = nullptr;
        source._size = 0;
    }
	
	// 5 : move assignment operator
	MyMovableClass& operator=(MyMovableClass &&source)  
    {
        std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
        if (this == &source)
            return *this;

        delete[] _data;

        _data = source._data;
        _size = source._size;

        source._data = nullptr;
        source._size = 0;

        return *this;
    }
	
	
	 
};


MyMovableClass createObject(int size){
  MyMovableClass obj(size); // regular constructor
  return obj; // return MyMovableClass object by value
}



int main()
{
    MyMovableClass obj1(10); // regular constructor
    MyMovableClass obj2(obj1); // copy constructor
    obj2 = obj1; // copy assignment operator
	  
	MyMovableClass obj3 = obj1;
	// Here, we are instantiating obj3 in the same statement; 
	// hence the copy assignment operator would not be called.


	// The returned value of createObject(10) is passed to the copy 
	// constructor. The function createObject() returns an instance of
	// MyMovableClass by value. In such a case, the compiler creates a 
	// temporary copy of the object as an rvalue, which is passed 
	// to the copy constructor.
	MyMovableClass obj4 = createObject(10);
   
  
  
	// The similar two expensive memory operations would be performed with 
	//        the assignment operator if we execute the following statement
	
	// MyMovableClass obj5 = createObject(10); 
	// obj5 = createObject(10);         // Call to copy assignment operator
  
    // 		In the above call to copy assignment operator, it would first erase the memory of obj5,
	// 		then reallocate it during the creation of the temporary object; and then 
	// 		copy the data from the temporary object to obj5.

	// 		From a performance viewpoint, this code involves far too many copies, making 
	//		 it inefficient - especially with large data structures.
	
	
	
	

	// "Move assignment operator" because MyMovableClass(200) is an rvalue reference
	// obj1 = MyMovableClass(200);  
	
	// "Move constructor" because MyMovableClass(300) is an rvalue reference
    // MyMovableClass obj6 = MyMovableClass(300);  
	
	
    return 0;
}