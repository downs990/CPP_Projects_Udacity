#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include<algorithm>

std::mutex mtx;
double result;

void printResult(int denom)
{
    std::cout << "for denom = " << denom << ", the result is " << result << std::endl;
}

void divideByNumber(double num, double denom)
{
    std::unique_lock<std::mutex> lck(mtx);
    /*
        IMPORTANT: 
        As before, the lock object lck will unlock the mutex in its destructor, i.e. 
        when the function divideByNumber returns and lck gets out of scope. In addition to 
        this automatic unlocking, std::unique_lock offers the additional flexibility to engage
        and disengage the lock as needed by manually calling the methods lock() and unlock(). 
    */
    try
    {
        // divide num by denom but throw an exception if division by zero is attempted
        if (denom != 0) 
        {   
            result = num / denom;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
            printResult(denom);
            lck.unlock();

            // do something outside of the lock
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
            /*
            DESCRIPTION: 
            In the example, the lock is released before some non-critical work is performed 
            (simulated by sleep_for) and re-engaged before some other work is performed in 
            the critical section and thus under the lock again at the end of the function. 
            
            This is particularly useful for optimizing performance and responsiveness when a
            significant amount of time passes between two accesses to a critical resource.
            */ 

            lck.lock(); 
            // do someting else under the lock
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
        else
        {
            throw std::invalid_argument("Exception from thread: Division by zero!");
        }
    }
    catch (const std::invalid_argument &e)
    {
        // notify the user about the exception and return
        std::cout << e.what() << std::endl;
        return; 
    }
}

int main()
{
    // create a number of threads which execute the function "divideByNumber" with varying parameters
    std::vector<std::future<void>> futures;
    for (double i = -5; i <= +5; ++i)
    {
        futures.emplace_back(std::async(std::launch::async, divideByNumber, 50.0, i));
    }

    // wait for the results
    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    return 0;
}