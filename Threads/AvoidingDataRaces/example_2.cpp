#include <iostream>
#include <thread>
#include <future>


/*
Description: 
The basic program structure is mostly identical to the previous example with the object v0 
being copied by value when passed to the thread function. This time however, even though a
 copy has been made, the original object v0 is modified when the thread function sets the 
 new name. This happens because the member _name is a pointer to a string and after copying, 
 even though the pointer variable has been duplicated, it still points to the same location 
 as its value (i.e. the memory location) has not changed. 
 
 Note that when the delay is removed in the thread function, the console output 
 varies between "Vehicle 2" and "Vehicle 3", depending on the system scheduler. Such an error 
 might go unnoticed for a long time. It could show itself well after a program has been 
 shipped to the client - which is what makes this error type so treacherous.
*/
class Vehicle
{
public:
    //default constructor
    Vehicle() : _id(0), _name(new std::string("Default Name"))
    {
        std::cout << "Vehicle #" << _id << " Default constructor called" << std::endl;
    }

    //initializing constructor
    Vehicle(int id, std::string name) : _id(id), _name(new std::string(name))
    {
        std::cout << "Vehicle #" << _id << " Initializing constructor called" << std::endl;
    }

    // setter and getter
    void setID(int id) { _id = id; }
    int getID() { return _id; }
    void setName(std::string name) { *_name = name; }
    std::string getName() { return *_name; }

private:
    int _id;
    std::string *_name;
};

int main()
{
    // create instances of class Vehicle
    Vehicle v0;    // default constructor
    Vehicle v1(1, "Vehicle 1"); // initializing constructor

    // launch a thread that modifies the Vehicle name
    std::future<void> ftr = std::async([](Vehicle v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
        v.setName("Vehicle 2");
    },v0);

    v0.setName("Vehicle 3");

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}