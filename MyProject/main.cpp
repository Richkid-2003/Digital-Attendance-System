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

// --- ATTENDANCE SESSION CLASS (Week 3) ---
class AttendanceSession {
private:
    string courseCode;
    string date;
    string startTime;
    int duration;

    struct AttendanceRecord {
        string studentName;
        string studentIndex;
        char status; 
    };

    vector<AttendanceRecord> records;

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

    void markAttendance(vector<Student>& students) {
        if (students.empty()) {
            cout << "No students registered to mark attendance for.\n";
            return;
        }

        records.clear(); 

        cout << "\n--- Marking Attendance for " << courseCode << " on " << date << " ---\n";
        
        for (int i = 0; i < students.size(); i++) {
            char status;
            bool valid = false;
            
            do {
                cout << "Is " << students[i].getName() << " (" << students[i].getIndexNumber() << ") present? (P/A/L): ";
                cin >> status;
                status = toupper(status);

                if (status == 'P' || status == 'A' || status == 'L') {
                    valid = true;
                } else {
                    cout << "Invalid input! Please enter P, A, or L.\n";
                }
            } while (!valid);

            AttendanceRecord rec;
            rec.studentName = students[i].getName();
            rec.studentIndex = students[i].getIndexNumber();
            rec.status = status;
            records.push_back(rec);
        }
        cout << "Attendance marking complete!\n";
    }

    // NEW: Generate Attendance Report
    void generateReport() {
        if (records.empty()) {
            cout << "No attendance marked for this session yet.\n";
            return;
        }

        int p = 0, a = 0, l = 0;

        cout << "\n--- Attendance Report (" << date << ") ---\n";
        cout << "Index\t\tStatus\tName\n";
        cout << "----------------------------------------\n";
        
        for (int i = 0; i < records.size(); i++) {
            cout << records[i].studentIndex << "\t\t" 
                 << records[i].status << "\t" 
                 << records[i].studentName << endl;

            if (records[i].status == 'P') p++;
            else if (records[i].status == 'A') a++;
            else if (records[i].status == 'L') l++;
        }

        cout << "----------------------------------------\n";
        cout << "SUMMARY: Present: " << p << " | Absent: " << a << " | Late: " << l << endl;
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

void processAttendance() {
    if (sessions.empty()) {
        cout << "Please create a session first.\n";
        return;
    }

    viewSessions();
    int choice;
    cout << "Select a session number to mark attendance: ";
    cin >> choice;

    if (choice > 0 && choice <= sessions.size()) {
        sessions[choice - 1].markAttendance(students);
    } else {
        cout << "Invalid session number.\n";
    }
}

// NEW: Helper function to select a session and view its report
void viewReport() {
    if (sessions.empty()) {
        cout << "No sessions available.\n";
        return;
    }

    viewSessions();
    int choice;
    cout << "Select a session number to view report: ";
    cin >> choice;

    if (choice > 0 && choice <= sessions.size()) {
        sessions[choice - 1].generateReport();
    } else {
        cout << "Invalid session number.\n";
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
        cout << "3. Create Lecture Session\n"; 
        cout << "4. View All Sessions\n";      
        cout << "5. Mark Attendance\n"; 
        cout << "6. View Attendance Report\n"; // NEW
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: createSession(); break; 
            case 4: viewSessions(); break;  
            case 5: processAttendance(); break; 
            case 6: viewReport(); break; // NEW
            case 0: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}