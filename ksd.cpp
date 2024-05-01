#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#define savedUsername "admin"
#define savedPassword "admin123"

using namespace std;

struct studentDetails {
    int sn;
    int phone;
    int sem;
    int guardianNo;
    float cgpa;
    string name;
    string address;
    string fatherName;
    string motherName;
    string faculty;
    string course;
};

bool authenticateUser(const string& username, const string& password)
{
    return (username == savedUsername && password == savedPassword);
}

// Function to clear the screen
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void addStudent(const string& fileName, const studentDetails& student)
{
    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;

        // Create the file if it does not exist
        file.open(fileName, ios::out);
        if (!file.is_open()) {
            cout << "Failed to create file." << endl;
            return;
        }
    }

    file << student.sn << "," << student.phone << "," << student.sem << "," << student.guardianNo << "," << student.cgpa << ","
         << student.name << "," << student.address << "," << student.fatherName << "," << student.motherName << ","
         << student.faculty << "," << student.course << endl;

    cout << "Student added successfully." << endl;
    file.close();
}


void deleteStudent(const string& fileName, int sn)
{
    ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    ofstream fileOut("temp.txt");
    if (!fileOut.is_open()) {
        cout << "Failed to open file." << endl;
        fileIn.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(fileIn, line)) {
        studentDetails std;
        istringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        std.sn = stoi(temp);

        if (std.sn == sn) {
            found = true;
            continue; // Skip this line, as we're deleting it
        }

        fileOut << line << endl;
    }

    fileIn.close();
    fileOut.close();

    if (!found) {
        cout << "Student with S.N. " << sn << " not found." << endl;
        remove("temp.txt");
        return;
    }

    // Rename temp file to original file
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());

    cout << "Student with S.N. " << sn << " deleted successfully." << endl;
}

void deleteStudent(const string& fileName, const string& name)
{
    ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    ofstream fileOut("temp.txt");
    if (!fileOut.is_open()) {
        cout << "Failed to open file." << endl;
        fileIn.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(fileIn, line)) {
        studentDetails std;
        istringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        std.sn = stoi(temp);
        getline(ss, std.name, ',');

        if (std.name == name) {
            found = true;
            continue; // Skip this line, as we're deleting it
        }

        fileOut << line << endl;
    }

    fileIn.close();
    fileOut.close();

    if (!found) {
        cout << "Student with name " << name << " not found." << endl;
        remove("temp.txt");
        return;
    }

    // Rename temp file to original file
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());

    cout << "Student with name " << name << " deleted successfully." << endl;
}

void searchStudent(const string& fileName, int searchBy, const string& query)
{
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        studentDetails std;
        istringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        std.sn = stoi(temp);
        getline(ss, temp, ',');
        std.phone = stoi(temp);
        getline(ss, temp, ',');
        std.sem = stoi(temp);
        getline(ss, temp, ',');
        std.guardianNo = stoi(temp);
        getline(ss, temp, ',');
        std.cgpa = stof(temp);
        getline(ss, std.name, ',');
        getline(ss, std.address, ',');
        getline(ss, std.fatherName, ',');
        getline(ss, std.motherName, ',');
        getline(ss, std.faculty, ',');
        getline(ss, std.course, ',');

        bool found = false;
        switch (searchBy) {
        case 1: // Search by S.N.
            if (to_string(std.sn) == query)
                found = true;
            break;
        case 2: // Search by Name
            if (std.name == query)
                found = true;
            break;
        case 3: // Search by Semester
            if (to_string(std.sem) == query)
                found = true;
            break;
        case 4: // Search by Course
            if (std.course == query)
                found = true;
            break;
        case 5: // Search by CGPA
            if (to_string(std.cgpa) == query)
                found = true;
            break;
        }
        if (found) {
            cout << "Student found:" << endl;
            cout << "S.N.: " << std.sn << endl;
            cout << "Phone: " << std.phone << endl;
            cout << "Semester: " << std.sem << endl;
            cout << "Guardian No: " << std.guardianNo << endl;
            cout << "CGPA: " << std.cgpa << endl;
            cout << "Name: " << std.name << endl;
            cout << "Address: " << std.address << endl;
            cout << "Father's Name: " << std.fatherName << endl;
            cout << "Mother's Name: " << std.motherName << endl;
            cout << "Faculty: " << std.faculty << endl;
            cout << "Course: " << std.course << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
    file.close();
}

int main()
{
    string username;
    string password;
    int loginAttempt = 0;

    while (loginAttempt < 3)
    {
        clearScreen();
        cout << "Enter Username: ";
        cin >> username;
        cout << "\nEnter Password: ";
        cin >> password;

        if (authenticateUser(username, password))
        {
            clearScreen();
            cout << "\n---------------------->   Welcome to the page!!   <---------------------------\n";
            cout << "1. Home\n2. Update Details\n3. Search\n4. Display\n5. Exit\n";

            // Student search functionality
            string fileName = "file.txt";
            int choice;
            int searchBy;
            string query;

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: // Home
                break;
            case 2: // Update Details
                {
                    cout << "1. Add\n2. Delete\n";
                    int updateChoice;
                    cout << "Enter update choice: ";
                    cin >> updateChoice;

                    switch (updateChoice) {
                    case 1: // Add
                        {
                            studentDetails newStudent;
                            cout << "Enter S.N.: ";
                            cin >> newStudent.sn;
                            cout << "Enter Name: ";
                            getline(cin, newStudent.name);
                            cout << "Enter Address: ";
                            getline(cin, newStudent.address);
                            cout << "Enter Phone: ";
                            cin >> newStudent.phone;
                            cout << "Enter Semester: ";
                            cin >> newStudent.sem;
                            cout << "Enter Father's Name: ";
                            getline(cin, newStudent.fatherName);
                            cout << "Enter Mother's Name: ";
                            getline(cin, newStudent.motherName);
                            cout << "Enter Guardian No: ";
                            cin >> newStudent.guardianNo;
                            cout << "Enter Faculty: ";
                            getline(cin, newStudent.faculty);
                            cout << "Enter Course: ";
                            getline(cin, newStudent.course);
                            cout << "Enter CGPA: ";
                            cin >> newStudent.cgpa;
                            cin.ignore(); // Ignore newline character

                            addStudent(fileName, newStudent);
                            break;
                        }
                    case 2: // Delete
                        {
                            cout << "1. Delete by S.N.\n2. Delete by Name\n";
                            int deleteChoice;
                            cout << "Enter delete choice: ";
                            cin >> deleteChoice;

                            switch (deleteChoice) {
                            case 1: // Delete by S.N.
                                {
                                    int sn;
                                    cout << "Enter S.N. of student to delete: ";
                                    cin >> sn;
                                    deleteStudent(fileName, sn);
                                    break;
                                }
                            case 2: // Delete by Name
                                {
                                    cin.ignore(); // Ignore newline character
                                    string name;
                                    cout << "Enter name of student to delete: ";
                                    getline(cin, name);
                                    deleteStudent(fileName, name);
                                    break;
                                }
                            default:
                                cout << "Invalid choice." << endl;
                                break;
                            }
                            break;
                        }
                    default:
                        cout << "Invalid choice." << endl;
                        break;
                    }
                    break;
                }
            case 3: // Search
                cout << "\nEnter search by (1: S.N., 2: Name, 3: Semester, 4: Course, 5: CGPA): ";
                cin >> searchBy;
                cin.ignore(); // Ignore newline character
                cout << "Enter search query: ";
                getline(cin, query);

                searchStudent(fileName, searchBy, query);
                break;
            case 4: // Display
                {
                    ifstream file(fileName);
                    string line;
                    cout << "Student details:" << endl;
                    while (getline(file, line)) {
                        studentDetails std;
                        istringstream ss(line);
                        string temp;

                        getline(ss, temp, ',');
                        std.sn = stoi(temp);
                        getline(ss, temp, ',');
                        std.phone = stoi(temp);
                        getline(ss, temp, ',');
                        std.sem = stoi(temp);
                        getline(ss, temp, ',');
                        std.guardianNo = stoi(temp);
                        getline(ss, temp, ',');
                        std.cgpa = stof(temp);
                        getline(ss, std.name, ',');
                        getline(ss, std.address, ',');
                        getline(ss, std.fatherName, ',');
                        getline(ss, std.motherName, ',');
                        getline(ss, std.faculty, ',');
                        getline(ss, std.course, ',');

                        cout << "S.N.: " << std.sn << endl;
                        cout << "Phone: " << std.phone << endl;
                        cout << "Semester: " << std.sem << endl;
                        cout << "Guardian No: " << std.guardianNo << endl;
                        cout << "CGPA: " << std.cgpa << endl;
                        cout << "Name: " << std.name << endl;
                        cout << "Address: " << std.address << endl;
                        cout << "Father's Name: " << std.fatherName << endl;
                        cout << "Mother's Name: " << std.motherName << endl;
                        cout << "Faculty: " << std.faculty << endl;
                        cout << "Course: " << std.course << endl;
                        cout << "---------------------------------" << endl;
                    }

                    file.close();
                    break;
                }
            case 5: // Exit
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }

            break;
        }
        else
        {
            cout << "\n---------------------->  'Invalid login attempt.'"<< " Please try again.  <---------------------------\n";
            cout << "\t\t\t\t\tAttempt " << loginAttempt + 1 << " of 3\n";
            loginAttempt++;

            if (loginAttempt == 3)
            {
                cout << "\n------------>     Too many login attempts! The program will now terminate. <-----------------\n";
                break;
            }

            // Pause to let the user read the message before trying again
            cout << "\nPress Enter to try again...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}
