#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>
#include <mutex>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int getID() { return _id; }

private:
    int _id;
};

    /*
    DESCRIPTION:
    We need to enable it to process write requests from several threads at the same time.
    Every time a request comes in from a thread, the object needs to add the new data to
    its internal storage. Our storage container will be an std::vector. As we need to protect 
    the vector from simultaneous access later, we also need to integrate a mutex into the class.

    As we already know, a mutex has the methods lock and unlock. In order to avoid data races, 
    the mutex needs to be locked every time a thread wants to access the vector and it needs to
    be unlocked one the write operation is complete. In order to avoid a program freeze due to 
    a missing unlock operation, we will be using a lock guard object, which automatically unlocks
    once the lock object gets out of scope.
    */

class WaitingVehicles
{
public:
    WaitingVehicles() {}


    /*
    DESCRIPTION:
    Another function within the WaitingVehicle class is printIDs(), which loops over all the 
    elements of the vector and prints their respective IDs to the console. One major difference 
    between pushBack() and printIDs() is that the latter function accesses all Vehicle objects by 
    looping through the vector while pushBack only accesses a single object - which is the newest 
    addition to the Vehicle vector.
    */
    void printIDs()
    {
        std::lock_guard<std::mutex> myLock(_mutex); // lock is released when myLock goes out of scope
        for(auto &v : _vehicles)
            std::cout << "   Vehicle #" << v.getID() << " is now waiting in the queue" << std::endl;
        
    }


    /*
    DESCRIPTION:
    In our modified pushBack function, we will first create a lock guard object and pass it 
    the mutex member variable. Now we can freely move the Vehicle object into our vector without 
    the danger of a data race. At the end of the function, there is a call to std::sleep_for, 
    which simulates some work and helps us to better expose potential concurrency problems. With 
    each new Vehicle object that is passed into the queue, we will see an output to the console.
    */
    void pushBack(Vehicle &&v)
    {
        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);
        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl; 
        _vehicles.emplace_back(std::move(v));

        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

private:
    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
    std::mutex _mutex;
};

int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; ++i)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    std::cout << "Collecting results..." << std::endl;
    queue->printIDs();

    /*
    DESCRIPTION:
    As can be seen, the Vehicle objects are added one at a time, with all threads duly waiting 
    for their turn. Then, once all Vehicle objects have been stored, the call to printIDs 
    prints the entire content of the vector all at once.
    */

    return 0;
}