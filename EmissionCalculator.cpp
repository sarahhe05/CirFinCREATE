#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int endColumnIndex(string line, int targetColumn);
int jumpColumnIndex(string line, int targetColumn);

int main(){
    
    ifstream inFS;                  // enable read file
    inFS.open("test.csv");

    if(!inFS.is_open()){            // check for potential open error
        cout << "test.csv cannot be opened" << endl;
        return 1;
    }

    int column = 1;
    string line, ingredientList, ingredient, unit;
    int amount;
    
    getline(inFS, line);     // we don't need the headers
    inFS.clear();

    while(getline(inFS, line)){
        // A function that returns the index of the start of a new column for ingredient column        
        int nextIndex = jumpColumnIndex(line, 2);
        int endIndex = endColumnIndex(line, 2);
        
        ingredientList = line.substr(nextIndex, endIndex - nextIndex + 1);
        cout << "Ingredient is the following: " << ingredientList << endl;

        inFS.clear();
    }

    /*
    A LIST OF ODD CASE
    1. The ingredient list does not match amount of ingredients in NER
    2. "1 fl oz or 3 cup of Salad Dressing" - double unit options
      - "1 (16 oz) box of Oranges"
    3. "fl oz" - two worded units
    4. Fractional numbers
    5. Improper units "1 can of Chicken soup"
    */


    // convert units
    // total emission for each recipe & store into vector

    inFS.close();

    // modify csv files

    return 0;
}

int jumpColumnIndex(string line, int targetColumn){
    int counterOfQuoteBracket = 0;
    int jumpIndex = -1;

    for(int i = 0; i < line.size() - 3 && jumpIndex == -1; ++i){
        string possibleQuoteBracket = line.substr(i,3);

        if(possibleQuoteBracket == ",\"["){  // this is the start of a special column
            ++counterOfQuoteBracket;
            if(counterOfQuoteBracket == targetColumn - 1){  // this is in context of our dataset
                jumpIndex = i + 3;
            }
        }
    }

    return jumpIndex;
}

int endColumnIndex(string line, int targetColumn){
    int counterOfQuoteBracket = 0; // helpful cases like ingredients
    int endIndex = -1;

    for(int i = 0; i < line.size() - 3 && endIndex == -1; ++i){
        string possibleQuoteBracket = line.substr(i,3);

        if(line.substr(i,3) == "]\","){
            counterOfQuoteBracket++;
            if(counterOfQuoteBracket == targetColumn - 1){
                endIndex = i-1;
            }
        }
    }

    return endIndex;
}