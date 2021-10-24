#include <iostream>
#include <assert.h>
#include <string>
using std::string;
using std::cout;


// TODO: Define Point class
class Point {
public:
  // TODO: Define public constructor
  Point(int x = 0, int y = 0) : x(x), y(y) {}

  // TODO: Define + operator overload
  Point operator+(const Point& addend) {
    Point sum;
    sum.x = x + addend.x;
    sum.y = y + addend.y;
    return sum;
  }

  // TODO: Declare attributes x and y
  int x, y;

  string toString(){
      return "x: " + std::to_string(x) + " y: " + std::to_string(y);
  }
};

// Test in main()
int main() {
  Point p1(10, 5), p2(2, 4);
  Point p3 = p1 + p2; // An example call to "operator +";

  cout << "Point 1: " << p1.toString() << "\n";
  cout << "Point 2: " << p2.toString() << "\n";
  cout << "Point 3: " << p3.toString() << "\n";
  assert(p3.x == p1.x + p2.x);
  assert(p3.y == p1.y + p2.y);
}