#include <iostream>
#include <fstream>
#include <string>

#include "../header/writeFile.hpp"

using namespace std;

    bool writeFile::open() {
        ofstream file(filename, ios::app); // ios::app is needed cuz it will wipe the file since its in write mode rather than append mode
        if (file.fail()) {
            cout << "Failed to open the file." << endl;
            return false;
        }
        return true;
    }
    void writeFile::close() {
        if (file.is_open()) {
            file.close();
            if (!file) {
                cout << "Failed to close the file." << endl;
            } 
            else {
                cout << "File closed successfully." << endl;
            }
        } 
        else {
            cout << "File is not open. Cannot close it." << endl;
        }
    }