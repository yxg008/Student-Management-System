#include <iostream>
#include <fstream>
#include <limits>
#include <stdlib.h>
#include <string>

using namespace std;

// ANSI Escape Codes for Colors
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";

// Student class definition
class Student {
    int admissionNo;
    char sname[20];
    char sgender;
    int std;
    float smarks;
    double spercentage;

public:
    void getData();
    void showData();
    int getAdmno() const { return admissionNo; }
};

// Function declarations
void project();
void addData(Student& s);
void displayData();
void deleteData();
void searchData();
void updateData();
void sortData();
void login();
void clearScreen();
void pauseScreen();

int main() {
    login();
    project();
    return 0;
}

void login() {
    
    cout << GREEN << "Login System Placeholder" << RESET << endl;
}

void project() {
    int ch;
    do {
        clearScreen();
        cout << BLUE << "**************STUDENT MANAGEMENT SYSTEM***************" << RESET << endl;
        cout << "1. Write Student Record" << endl;
        cout << "2. Read Student Record" << endl;
        cout << "3. Update Student Record" << endl;
        cout << "4. Delete Student Record" << endl;
        cout << "5. Search Student Record" << endl;
        cout << "6. Sort Student Records" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        clearScreen();

        Student s; 
        switch (ch) {
            case 1: addData(s); break;
            case 2: displayData(); break;
            case 3: updateData(); break;
            case 4: deleteData(); break;
            case 5: searchData(); break;
            case 6: sortData(); break;
        }

        pauseScreen();
    } while (ch);
}

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pauseScreen() {
    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Student::getData() {
    cout << YELLOW << "\n\n*******Enter Student Data*******" << RESET << endl;
    cout << "Admission No.: "; cin >> admissionNo;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a number." << RESET << endl;
        return;
    }
    cout << "Full Name: "; cin.ignore(); cin.getline(sname, 20);
    cout << "Gender (M/F): "; cin >> sgender;
    cout << "Class: "; cin >> std;
    cout << "Total Marks (/500): "; cin >> smarks;
    spercentage = smarks * 100.0 / 500.00;
}

void Student::showData() {
    cout << GREEN << "\n\n*******Student Details*******" << RESET << endl;
    cout << "Admission No.: " << admissionNo << endl;
    cout << "Full Name: " << sname << endl;
    cout << "Gender: " << sgender << endl;
    cout << "Class: " << std << endl;
    cout << "Total Marks (/500): " << smarks << endl;
    cout << "Percentage: " << spercentage << "%" << endl;
}

void addData(Student& s) {
    ofstream fout;
    fout.open("Stu.txt", ios::out | ios::app | ios::binary);
    if (!fout.is_open()) {
        cout << RED << "Failed to open file for writing." << RESET << endl;
        return;
    }
    s.getData();
    fout.write((char*)&s, sizeof(s));
    fout.close();
    cout << RED << "\n\n*******Data Successfully Saved to File*******" << RESET << endl;
}

void displayData() {
    ifstream fin;
    fin.open("Stu.txt", ios::in | ios::binary);
    if (!fin.is_open()) {
        cout << RED << "Failed to open file for reading." << RESET << endl;
        return;
    }
    Student s;
    while (fin.read((char*)&s, sizeof(s))) {
        s.showData();
    }
    fin.close();
}

void updateData() {
    int admNo, found = 0;
    Student temp, s;
    fstream file;

    cout << YELLOW << "Enter Admission Number to Update: " << RESET;
    cin >> admNo;

    file.open("Stu.txt", ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << RED << "Failed to open file." << RESET << endl;
        return;
    }

    while (!file.eof()) {
        long pos = file.tellg(); 
        file.read((char*)&s, sizeof(s));
        if (s.getAdmno() == admNo) {
            cout << GREEN << "Current Details of Student:" << RESET << endl;
            s.showData();
            cout << YELLOW << "\nEnter New Details of Student:" << RESET << endl;
            temp.getData();
            file.seekg(pos); 
            file.write((char*)&temp, sizeof(temp));
            found = 1;
            break;
        }
    }

    file.close();
    if (found)
        cout << GREEN << "Student record updated successfully." << RESET << endl;
    else
        cout << RED << "No record found with Admission Number: " << admNo << RESET << endl;
}

void deleteData() {
    int admNo, found = 0;
    ifstream fin;
    ofstream fout;
    Student s; 

    cout << YELLOW << "Enter Admission Number to Delete: " << RESET;
    cin >> admNo;

    fin.open("Stu.txt", ios::in | ios::binary);
    fout.open("Temp.txt", ios::out | ios::binary);

    if (!fin.is_open() || !fout.is_open()) {
        cout << RED << "Error opening files!" << RESET << endl;
        return;
    }

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getAdmno() != admNo) {
            fout.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }

    fin.close();
    fout.close();

    remove("Stu.txt");
    rename("Temp.txt", "Stu.txt");

    if (found)
        cout << GREEN << "Student record deleted successfully." << RESET << endl;
    else
        cout << RED << "No record found with Admission Number: " << admNo << RESET << endl;
}

void searchData() {
    int admNo, found = 0;
    ifstream fin;
    Student s; 

    cout << YELLOW << "Enter Admission Number to Search: " << RESET;
    cin >> admNo;

    fin.open("Stu.txt", ios::in | ios::binary);
    if (!fin.is_open()) {
        cout << RED << "Failed to open file for reading." << RESET << endl;
        return;
    }

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getAdmno() == admNo) {
            s.showData();
            found = 1;
            break;
        }
    }

    fin.close();
    if (!found)
        cout << RED << "No record found with Admission Number: " << admNo << RESET << endl;
}

bool compareByAdmissionNo(const Student &a, const Student &b) {
    return a.getAdmno() < b.getAdmno();
}

void sortData() {
    vector<Student> students;
    Student temp;
    ifstream fin;
    ofstream fout;

    fin.open("Stu.txt", ios::in | ios::binary);
    if (!fin.is_open()) {
        cout << RED << "Failed to open file for reading." << RESET << endl;
        return;
    }


    while (fin.read((char*)&temp, sizeof(Student))) {
        students.push_back(temp);
    }
    fin.close();

    
    if (!fin.eof() && fin.fail()) {
        cout << RED << "Error occurred while reading the file." << RESET << endl;
        return;
    }

 
    sort(students.begin(), students.end(), compareByAdmissionNo);

   
    fout.open("Stu.txt", ios::out | ios::binary);
    if (!fout.is_open()) {
        cout << RED << "Failed to open file for writing." << RESET << endl;
        return;
    }

    for (size_t i = 0; i < students.size(); ++i) {
        fout.write((char*)&students[i], sizeof(Student));
    }
    fout.close();

    cout << GREEN << "Data sorted successfully by Admission Number." << RESET << endl;
}

    

