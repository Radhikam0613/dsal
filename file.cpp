// Department maintains a student information. The file contains roll number,
// name, division and address. Allow user to add, delete information of student.
// Display information of particular employee. If record of student does not exist an
// appropriate message is displayed. If it is, then the system displays the student
// details. Use sequential file to main the data.
// add student
// search student
// delete student
// display student
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string studentFile = "students.txt";

void addStudent() {
    ofstream file(studentFile, ios::app);
    string rollno, name, division, address;
    cout << "Enter Roll No, Name, Division, Address: ";
    cin >> rollno >> name >> division >> address;
    file << rollno << "," << name << "," << division << "," << address << endl;
}

void searchStudent() {
    ifstream file(studentFile);
    string name, line;
    bool found = false;
    cout << "Enter Name to search:- ";
    cin >> name;
    while (getline(file, line)) {
        if (line.find("," + name + ",") != string::npos) {// npos is like "not found" position in a string
            cout << "Found:- " << line << endl;
            found = true;
        }
    }
    if (!found)
        cout << "Student not found.\n";
}

void deleteStudent() {
    ifstream file(studentFile);
    ofstream temp("temp.txt");
    string rollno, line;
    bool found = false;
    cout << "Enter Roll No to delete: ";
    cin >> rollno;
    while (getline(file, line)) {
        if (line.substr(0, line.find(",")) != rollno)
            temp << line << endl;
        else
            found = true;
    }
    file.close();
    temp.close();
    if (found) {
        remove(studentFile.c_str()); // converets file into desired type and deletes
        rename("temp.txt", studentFile.c_str()); // renames file after converting in desired type
        cout << "Record deleted successfully.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void displayStudent() {
    ifstream file(studentFile);
    string rollno, line;
    bool found = false;
    cout << "Enter Roll No to display: ";
    cin >> rollno;
    while (getline(file, line)) {
        if (line.substr(0, line.find(",")) == rollno) {
            cout << "Details: " << line << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student record not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n1. Add Student\n2. Delete Student\n3. Search Student by Name\n4. Display Student by Roll No\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: searchStudent(); break;
            case 4: displayStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
    return 0;
}