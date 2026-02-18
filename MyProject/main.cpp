// ==========================================
// CAPSTONE PROJECT: DIGITAL ATTENDANCE SYSTEM
// COURSE: EEE227
// ==========================================
#include <iostream>
#include <vector>
#include <string>
#include <fstream> // NEW: Required for file handling
#include <sstream> // NEW: Required for string parsing

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

// --- ATTENDANCE SESSION CLASS ---
class AttendanceSession {
private:
    string courseCode;
    string date;
    string startTime;
    int duration;

public:
    struct AttendanceRecord {
        string studentName;
        string studentIndex;
        char status; 
    };

    vector<AttendanceRecord> records;

    AttendanceSession(string code, string dt, string time, int dur) {
        courseCode = code;
        date = dt;
        startTime = time;
        duration = dur;
    }

    // Getters for File Saving
    string getCode() { return courseCode; }
    string getDate() { return date; }
    string getTime() { return startTime; }
    int getDuration() { return duration; }

    // Manually add a record (used during file loading)
    void addRecord(string name, string index, char status) {
        AttendanceRecord rec;
        rec.studentName = name;
        rec.studentIndex = index;
        rec.status = status;
        records.push_back(rec);
    }

    void displaySession() {
        cout << "Course: " << courseCode << " | Date: " << date 
             << " | Time: " << startTime << " | Duration: " << duration << " hrs\n";
    }

    void markAttendance(vector<Student>& students) {
        if (students.empty()) {
            cout << "No students registered.\n";
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

// --- FILE HANDLING FUNCTIONS (NEW FOR WEEK 4) ---

void saveData() {
    // 1. Save Students
    ofstream studentFile("students.txt");
    if (studentFile.is_open()) {
        for (int i = 0; i < students.size(); i++) {
            studentFile << students[i].getName() << "," << students[i].getIndexNumber() << endl;
        }
        studentFile.close();
    }

    // 2. Save Sessions
    ofstream sessionFile("sessions.txt");
    if (sessionFile.is_open()) {
        for (int i = 0; i < sessions.size(); i++) {
            sessionFile << "SESSION|" << sessions[i].getCode() << "|" 
                        << sessions[i].getDate() << "|" 
                        << sessions[i].getTime() << "|" 
                        << sessions[i].getDuration() << endl;
            
            for (int j = 0; j < sessions[i].records.size(); j++) {
                sessionFile << "RECORD|" << sessions[i].records[j].studentName << "|"
                            << sessions[i].records[j].studentIndex << "|"
                            << sessions[i].records[j].status << endl;
            }
        }
        sessionFile.close();
    }
    cout << "Data saved successfully to files!\n";
}

void loadData() {
    // 1. Load Students
    ifstream studentFile("students.txt");
    if (studentFile.is_open()) {
        string line, name, index;
        while (getline(studentFile, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, index, ',');
            if (!name.empty() && !index.empty()) {
                students.push_back(Student(name, index));
            }
        }
        studentFile.close();
    }

    // 2. Load Sessions
    ifstream sessionFile("sessions.txt");
    if (sessionFile.is_open()) {
        string line;
        AttendanceSession* currentSession = NULL; 

        while (getline(sessionFile, line)) {
            stringstream ss(line);
            string part;
            vector<string> parts;

            while (getline(ss, part, '|')) {
                parts.push_back(part);
            }

            if (parts.size() > 0) {
                if (parts[0] == "SESSION" && parts.size() == 5) {
                    int dur = 0;
                    stringstream(parts[4]) >> dur; 
                    AttendanceSession newSession(parts[1], parts[2], parts[3], dur);
                    sessions.push_back(newSession);
                    currentSession = &sessions.back(); 
                } 
                else if (parts[0] == "RECORD" && parts.size() == 4 && currentSession != NULL) {
                    char status = parts[3][0];
                    currentSession->addRecord(parts[1], parts[2], status);
                }
            }
        }
        sessionFile.close();
    }
}

// --- STANDARD FUNCTIONS ---
void registerStudent() {
    string name, index;
    cin.ignore(); 
    cout << "\n--- Register New Student ---\n";
    cout << "Enter Full Name: "; getline(cin, name);
    cout << "Enter Index Number: "; cin >> index;
    students.push_back(Student(name, index));
    cout << "Student registered successfully!\n";
}

void viewStudents() {
    cout << "\n--- Registered Students ---\n";
    if (students.empty()) cout << "No students registered yet.\n";
    else for (int i = 0; i < students.size(); i++) { cout << i + 1 << ". "; students[i].display(); }
}

void createSession() {
    string code, date, time; int duration;
    cout << "\n--- Create Lecture Session ---\n";
    cout << "Course Code: "; cin >> code;
    cout << "Date (YYYY-MM-DD): "; cin >> date;
    cout << "Start Time (HH:MM): "; cin >> time;
    cout << "Duration (hrs): "; cin >> duration;
    sessions.push_back(AttendanceSession(code, date, time, duration));
    cout << "Session created successfully!\n";
}

void viewSessions() {
    cout << "\n--- Scheduled Sessions ---\n";
    if (sessions.empty()) cout << "No sessions created yet.\n";
    else for (int i = 0; i < sessions.size(); i++) { cout << i + 1 << ". "; sessions[i].displaySession(); }
}

void processAttendance() {
    if (sessions.empty()) { cout << "Create a session first.\n"; return; }
    viewSessions();
    int choice; cout << "Select a session number to mark attendance: "; cin >> choice;
    if (choice > 0 && choice <= sessions.size()) sessions[choice - 1].markAttendance(students);
    else cout << "Invalid session number.\n";
}

void viewReport() {
    if (sessions.empty()) { cout << "No sessions available.\n"; return; }
    viewSessions();
    int choice; cout << "Select a session number to view report: "; cin >> choice;
    if (choice > 0 && choice <= sessions.size()) sessions[choice - 1].generateReport();
    else cout << "Invalid session number.\n";
}

// --- MAIN PROGRAM ---
int main() {
    loadData(); // NEW: Load previous data when program starts!

    int choice;
    do {
        cout << "\n============================================\n";
        cout << "   FINAL DIGITAL ATTENDANCE SYSTEM          \n";
        cout << "============================================\n";
        cout << "1. Register Student\n";
        cout << "2. View All Students\n";
        cout << "3. Create Lecture Session\n"; 
        cout << "4. View All Sessions\n";      
        cout << "5. Mark Attendance\n"; 
        cout << "6. View Attendance Report\n"; 
        cout << "0. Save & Exit\n"; // NEW: Notice the "Save & Exit" label
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: createSession(); break; 
            case 4: viewSessions(); break;  
            case 5: processAttendance(); break; 
            case 6: viewReport(); break; 
            case 0: 
                saveData(); // NEW: Save all data before exiting!
                cout << "Exiting program. Goodbye!\n"; 
                break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}