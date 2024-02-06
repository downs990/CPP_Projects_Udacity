#include <iostream>

// Functor class
class AddFunctor {
public:
    // Overloading the function call operator
    int operator()(int a, int b) const {
        return a + b;
    }
};

int main() {
    // Creating an instance of the AddFunctor class
    AddFunctor addFunctor;

    // Using the functor as if it were a function
    int result = addFunctor(3, 4);

    // Displaying the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}
