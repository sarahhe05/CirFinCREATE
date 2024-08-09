#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool inVector(vector<string> const search);

int main(int argc, char* argv[]) {
    // reads recipes.csv
    // takes in ingreidnets of research
    // keep track of the top of 5 (at most) recipe with least carbon amount
    // print results
    vector<string> ingredientOfSearch;
    ifstream inFS("recipes.csv");
    
    if(!inFS.is_open()){            // check for potential open error
        cout << "test.csv cannot be opened" << endl;
        return 1;
    }
    // offload the ingredients of search into vector
    for(int i = 2; i < argc; ++i){
        ingredientOfSearch.push_back(argv[i]);
    }
}

bool inVector(vector<string> const search){}