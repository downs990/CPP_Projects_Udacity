#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::istringstream;



// TODO: Add the ParseLine function here.
vector<int> ParseLine(string lineFromFile){

    vector<int> result = {};
    istringstream my_stream(lineFromFile);

    int n;
    char c;
    
    // Testing to see if the stream was successful and printing results.
    while (my_stream) {
        my_stream >> n >> c;
         
        if (my_stream) { 
            result.push_back(n);
        }
    }

    return result;
}


void PrintVector(vector<int> v) {
  cout << "{ ";
  for (auto item : v) {
    cout << item << " ";
  }
  cout << "}" << "\n";
}

void TestParseLine() {
  cout << "----------------------------------------------------------" << "\n";
  cout << "TestParseLine: ";
  string line = "0,1,0,0,0,0,";
  vector<int> solution_vect{0,1,0,0,0,0};
  vector<int> test_vect;
  test_vect = ParseLine(line);
  if (test_vect != solution_vect) {
    cout << "failed" << "\n";
    cout << "\n" << "Test input string: " << line << "\n";
    cout << "Your parsed line: ";
    PrintVector(test_vect);
    cout << "\n";
  } else {
    cout << "passed" << "\n";
  }
  cout << "----------------------------------------------------------" << "\n";
  return;
}