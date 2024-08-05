#include <iostream>
#include <fstream>
#include <string>

#include "../header/writeFile.hpp"

using namespace std;

int main() {
    writeFile wf("example.csv");

    if (!wf.open()) {
        return 1;
    }

    wf.close();

    return 0;
}