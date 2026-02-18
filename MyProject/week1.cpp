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

// --- GLOBAL VARIABLES ---
// We use a vector to store students dynamically
vector<Student> students;

// --- HELPER FUNCTIONS ---

// Function to register a new student
void registerStudent() {
    string name, index;
    
    // Clear input buffer to handle spaces in names
    cin.ignore(); 
    
    cout << "\n--- Register New Student ---\n";
    cout << "Enter Full Name: ";
    getline(cin, name);
    
    cout << "Enter Index Number: ";
    cin >> index;

    // Create a new student object and add it to our list
    Student newStudent(name, index);
    students.push_back(newStudent);

    cout << "Student registered successfully!\n";
}

// Function to view all students
void viewStudents() {
    cout << "\n--- Registered Students ---\n";
    if (students.empty()) {
        cout << "No students registered yet.\n";
    } else {
        for (int i = 0; i < students.size(); i++) {
            cout << i + 1 << ". ";
            students[i].display();
        }
    }
}

// --- MAIN PROGRAM ---
int main() {
    int choice;

    do {
        cout << "\n============================================\n";
        cout << "   DIGITAL ATTENDANCE SYSTEM (WEEK 1)      \n";
        cout << "============================================\n";
        cout << "1. Register Student\n";
        cout << "2. View All Students\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 0:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}