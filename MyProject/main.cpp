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
    AttendanceSession(string code, string dt, string time, int dur) {
        courseCode = code;
        date = dt;
        startTime = time;
        duration = dur;
    }

    void displaySession() {
        cout << "Course: " << courseCode << " | Date: " << date 
             << " | Time: " << startTime << " | Duration: " << duration << " hrs\n";
    }
};

// --- GLOBAL VARIABLES ---
vector<Student> students;
vector<AttendanceSession> sessions; 

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

void createSession() {
    string code, date, time;
    int duration;

    cout << "\n--- Create Lecture Session ---\n";
    cout << "Enter Course Code (e.g., EEE227): ";
    cin >> code;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter Start Time (HH:MM): ";
    cin >> time;
    cout << "Enter Duration (in hours): ";
    cin >> duration;

    AttendanceSession newSession(code, date, time, duration);
    sessions.push_back(newSession);

    cout << "Session created successfully!\n";
}

void viewSessions() {
    cout << "\n--- Scheduled Sessions ---\n";
    if (sessions.empty()) {
        cout << "No sessions created yet.\n";
    } else {
        for (int i = 0; i < sessions.size(); i++) {
            cout << i + 1 << ". ";
            sessions[i].displaySession();
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
        cout << "3. Create Lecture Session\n"; // NEW
        cout << "4. View All Sessions\n";      // NEW
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: createSession(); break; // NEW
            case 4: viewSessions(); break;  // NEW
            case 0: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}