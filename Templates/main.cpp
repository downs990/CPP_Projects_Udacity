#include <assert.h>
#include <string>
#include <sstream>
using std::string;
 

template <typename MyKey, typename MyValue>
class Mapping {
public:

    Mapping(MyKey key, MyValue value) : key(key), value(value) {}

    string Print() const {
        std::ostringstream stream;
        stream << key << ": " << value;
        return stream.str();
    }
    
    MyKey key;
    MyValue value;
};

// Test
int main() {
  Mapping<string, int> mapping("age", 20);
  assert(mapping.Print() == "age: 20");
}