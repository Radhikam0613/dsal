// Implementation of a direct access file -Insertion and deletion of a record from a direct access file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const string student = "students.txt";

void addStudent(string rollno, string name, string division, string address) {
    ofstream file(student, ios::app);
    file << rollno << "," << name << "," << division << "," << address << endl;
    file.close();
}

void deleteStudent(string rollno) {
    ifstream file(student);
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.substr(0, line.find(",")) != rollno)
            temp << line << endl;
        else
            found = true;
    }
    file.close();
    temp.close();
    remove(student.c_str()); // converets file into desired type and deletes
    rename("temp.txt", student.c_str()); // renames file after converting in desired type
    if (found == false) {
	cout << "Student record not found.\n";
    }
}

void searchStudent(string name) {
	ifstream file(student);
	string line;
	bool found = false;
	while (getline(file, line)) {
		if (line.find("," + name + ",") != string::npos) { // npos is like "not found" position in a string
		    cout << "Found: \n" << line << endl;
		    found = true;
		}
    	}
	file.close();
	if (found == false) {
		cout << "Student not found.\n";
	}
		
}
	
void displayStudent(string rollno) {
	ifstream file(student);
	string line;
	bool found = false;
	while (getline(file, line)) {
	if (line.substr(0, line.find(",")) == rollno) {
	    cout << "Details: \n" << line << endl;
	    found = true;
	    break;
	}
	}
	file.close();
	if (found == false) {
		cout << "Student with roll number "<< rollno << "'s record was not found.\n";
	}
}

int main() {
	addStudent("101", "Radhika", "A", "Pune");
	addStudent("102", "Mankar", "B", "Nagpur");
	addStudent("103", "Hehe", "C", "I2IT");
	deleteStudent("101");
	displayStudent("101");
	displayStudent("102");
	searchStudent("Hehe");
	return 0;
}