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
    Student(string name, string index) {
        fullName = name;
        indexNumber = index;
    }

    string getIndexNumber() { return indexNumber; }
    string getName() { return fullName; }

    void display() {
        cout << "Index: " << indexNumber << " | Name: " << fullName << endl;
    }
};

// --- ATTENDANCE SESSION CLASS (Week 2) ---
class AttendanceSession {
private:
    string courseCode;
    string date;
    string startTime;
    int duration;

public:
    // Constructor
    AttendanceSession(string code, string dt, string time, int dur) {
        courseCode = code;
        date = dt;
        startTime = time;
        duration = dur;
    }

    // Display Session Details
    void displaySession() {
        cout << "Course: " << courseCode << " | Date: " << date 
             << " | Time: " << startTime << " | Duration: " << duration << " hrs\n";
    }
};

// --- GLOBAL VARIABLES ---
vector<Student> students;

// --- HELPER FUNCTIONS ---
void registerStudent() {
    string name, index;
    cin.ignore(); 
    cout << "\n--- Register New Student ---\n";
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Index Number: ";
    cin >> index;

    Student newStudent(name, index);
    students.push_back(newStudent);
    cout << "Student registered successfully!\n";
}

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
        cout << "   DIGITAL ATTENDANCE SYSTEM               \n";
        cout << "============================================\n";
        cout << "1. Register Student\n";
        cout << "2. View All Students\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 0: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}