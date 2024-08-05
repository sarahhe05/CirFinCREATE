#ifndef writeFile_hpp
#define writeFile_hpp

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class writeFile{

    private:
        string filename;
        ofstream file;

    public:
        writeFile(const string& fname) : filename(fname) {}
        bool open();
        void close();

};



#endif