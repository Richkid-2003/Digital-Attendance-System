#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- STUDENT CLASS ---
class Student {
private:
    string fullName;
    string indexNumber;

public:
    // Constructor
    Student(string name, string index) {
        fullName = name;
        indexNumber = index;
    }

    // Getters
    string getIndexNumber() { return indexNumber; }
    string getName() { return fullName; }

    // Display Student Details
    void display() {
        cout << "Index: " << indexNumber << " | Name: " << fullName << endl;
    }
};