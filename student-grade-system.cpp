#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int SUBJECTS = 8;
const int MAX_STUDENTS = 100;

struct Student {
    string name;
    int seatNumber;
    int grades[SUBJECTS];
    int total;
    float average;
    string grade;
    string status;
};

Student students[MAX_STUDENTS];
int studentCount = 0;

// Input grade with range validation
int inputGrade(string subject) {
    int grade;
    while (true) {
        cout << "Enter grade for " << subject << " (0 - 100): ";
        cin >> grade;
        if (grade < 0 || grade > 100) {
            cout << "❌ Error: Grade must be between 0 and 100\n";
        } else {
            break;
        }
    }
    return grade;
}

// Calculate GPA grade based on average
string calculateGrade(float average) {
    if (average >= 90) return "Excellent";
    else if (average >= 80) return "Very Good";
    else if (average >= 60) return "Good";
    else if (average >= 50) return "Acceptable";
    else return "Failed";
}

// Add a new student to the system
void addStudent() {
    // Check if system has reached maximum capacity
    if (studentCount >= MAX_STUDENTS) {
        cout << "\n❌ Error: Cannot add more students. System full!\n";
        return;
    }

    Student newStudent;

    cout << "\nEnter Student Name: ";
    cin.ignore(); // Clears the newline from the main menu choice
    getline(cin, newStudent.name);

    cout << "Enter Seat Number: ";
    cin >> newStudent.seatNumber;

    string subjects[SUBJECTS] = {
        "Quran", "Islamic Studies", "Arabic", "English", 
        "Physics", "Chemistry", "Biology", "Mathematics"
    };

    bool failed = false;
    newStudent.total = 0;

    // Input grades for all subjects
    for (int i = 0; i < SUBJECTS; i++) {
        newStudent.grades[i] = inputGrade(subjects[i]);
        if (newStudent.grades[i] < 50) {
            failed = true;
        }
        newStudent.total += newStudent.grades[i];
    }

    // Determine student status
    if (failed) {
        newStudent.status = "Failed";
        newStudent.total = 0;
        newStudent.average = 0;
        newStudent.grade = "-";
    } else {
        newStudent.status = "Passed";
        newStudent.average = newStudent.total / (float)SUBJECTS;
        newStudent.grade = calculateGrade(newStudent.average);
    }

    // Save student record
    students[studentCount] = newStudent;
    studentCount++;

    cout << "\n✅ Student data saved successfully!\n";
}

// Search for a student record by seat number
void searchStudent() {
    int seatNumber;
    cout << "\nEnter Seat Number: ";
    cin >> seatNumber;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].seatNumber == seatNumber) {
            cout << "\n===== Student Result =====\n";
            cout << "Name       : " << students[i].name << endl;
            cout << "Seat Number: " << students[i].seatNumber << endl;

            string subjects[SUBJECTS] = {
                "Quran", "Islamic Studies", "Arabic", "English", 
                "Physics", "Chemistry", "Biology", "Mathematics"
            };

            // Display subject grades
            for (int j = 0; j < SUBJECTS; j++) {
                cout << subjects[j] << ": " << students[i].grades[j] << endl;
            }

            cout << "Status     : " << students[i].status << endl;

            if (students[i].status == "Passed") {
                cout << "Total      : " << students[i].total << endl;
                cout << fixed << setprecision(2);
                cout << "Average    : " << students[i].average << "%" << endl;
                cout << "Grade      : " << students[i].grade << endl;
            } else {
                cout << "Total      : -\n";
                cout << "Average    : -\n";
                cout << "Grade      : -\n";
            }
            return;
        }
    }
    cout << "❌ Error: No student found with this seat number\n";
}

// Main program menu
int main() {
    int choice;
    do {
        cout << "\n===== Student Grades Management System =====\n";
        cout << "1. Add New Student\n";
        cout << "2. Search Student Result\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 0:
                cout << "👋 Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "❌ Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
