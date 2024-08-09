#include <iostream>
#include <string>
#include <vector>
#include <fstream>
// #include "recipe.hpp"

using namespace std;

bool inVector(vector<string> const NER, vector<string> const search, string checkStatus);
string getColumnInfo(string line, int targetColumn); //gets Column Info for any column except for 5th one
int jumpColumnIndex(string line, int targetColumn);
int endColumnIndex(string line, int targetColumn);
void fillVector(string data, vector<string>& cleanVector);


int main(int argc, char* argv[]) {
    // reads recipes.csv
    // takes in ingreidnets of research
    // keep track of the top of 5 (at most) recipe with least carbon amount
    // print results
    vector<string> ingredientOfSearch;
    ifstream inFS("recipes.csv");
    
    if(!inFS.is_open()){            // check for potential open error
        cout << "recipes.csv cannot be opened" << endl;
        return 1;
    }

    // string checkStatus = argv[2];       // tells us if the checkbox is checked. If it's checked, then the search must match exactly, down to the size

    // offload the ingredients of search into vector
    for(int i = 3; i < argc; ++i){
        ingredientOfSearch.push_back(argv[i]);
    }
    
    string line5;
    // recipe FirstLeastEmission, SecondLeastEmission, ThirdLeastEmission, FourthLeastEmission, FifthLeastEmission;
    getline(inFS, line5);
    line5.clear();

    while(getline(inFS, line5)){
        vector<string> cleanNER;
        string rawNER = getColumnInfo(line5, 4);
        fillVector(rawNER, cleanNER);
        double carbonEmissionAmt = stod(getColumnInfo(line5, 6));

        // string rawIngredient = getColumnInfo(line5, 2);
        // vector<string> cleanIngredient;
        // fillVector(rawIngredient, cleanIngredient);

        // for(int i = 0; i < cleanIngredient.size(); ++i){
        //     cout << "Item " << i + 1<< ": " << cleanIngredient.at(i) << endl;
        // }
        
        string rawdirection = getColumnInfo(line5, 3);
        vector<string> cleanDirections;
        fillVector(rawdirection, cleanDirections);

        for(int i = 0; i < cleanDirections.size(); ++i){
            cout << "Item " << i + 1 << ": " << cleanDirections.at(i) << endl;
        }
        
        // extract rawNER into vector NER
        line5.clear();
    }
    cout << endl;
    inFS.clear();

    inFS.close();

    return 0;
}

//two filtering systems: (1) only ingredients tagged vs. (2) ingredients contained
bool inVector(vector<string> const NER, vector<string> const search, string checkStatus){ //checks what the user wants is in NER
    bool isIn = false;

    if(checkStatus == "checked" && NER.size() != search.size()){    // Automatically not equal if it's not the same size... so false for (1)
        return false;
    }

    for(int i = 0; i < search.size(); ++i){ // works fine for (1), covers the last case... works for (2) because we know search is always less or equal NER size >> we only need to check if search is in NER
        isIn = false;   // we cannot assume the next search Item is within NER if the first search item is
        for(int j = 0; j < NER.size(); ++j){
            if(NER.at(j) == search.at(i)){
                isIn = true;
            }
        }
    }
    return isIn;
}

string getColumnInfo(string line, int targetColumn){
    string rawColumnInfo;
    int nextIndex = -1;
    int endIndex = -1;

    if(targetColumn == 1){
        for(int i = 0; i < line.size(); ++i){
            if(line.at(i) == ','){
                endIndex = i;
                break;
            }
        }
        rawColumnInfo = line.substr(0,endIndex);
    }
    else if(targetColumn > 1 && targetColumn < 5){
        nextIndex = jumpColumnIndex(line, targetColumn);    // A function that returns the index of the start of a new column for ingredient column        
        endIndex = endColumnIndex(line, targetColumn);
        rawColumnInfo = line.substr(nextIndex, endIndex - nextIndex + 1);
    }
    else{ //Column 5 intentionally doesn't work in this function
        for(int i = line.size() - 1; i > 0; --i){
            if(line.at(i) == ','){
                nextIndex = i + 1;
                break;
            }
        }
        rawColumnInfo = line.substr(nextIndex, line.size() - nextIndex);
    }

    return rawColumnInfo;
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
        else if(possibleQuoteBracket == ",[\'"){  // this is the start of a special column
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

        if(possibleQuoteBracket == "]\"," ){
            counterOfQuoteBracket++;
            if(counterOfQuoteBracket == targetColumn - 1){
                endIndex = i-1;
            }
        }
        else if(possibleQuoteBracket == "\'],"){
            counterOfQuoteBracket++;
            if(counterOfQuoteBracket == targetColumn - 1){
                endIndex = i;
            }
        }
    }

    return endIndex;
}

// we are using this function to extract 3 columns: NER, ingreident, directions
void fillVector(string rawData, vector<string>& cleanVector){
    string data;
    bool toContinue = false;
    string possibleQuoteBracket;
    

    for(int i = 1; i < rawData.size() - 1; ++i){
        if(i < rawData.size() - 3){
            possibleQuoteBracket = rawData.substr(i,3);
        }
        else{
            toContinue = true;
        }

        if(possibleQuoteBracket == "\', " || i == rawData.size() - 2){
            if(i == rawData.size() - 2){
                data.push_back(rawData.at(i));
            }
            cleanVector.push_back(data);
            data.clear();
            i = i + 3;
        }
        else if(!toContinue){
            data.push_back(rawData.at(i));
        }
        else{
            data.push_back(rawData.at(i));
        }
    }

    // fill Ingredients for ingredientList
    // for(int i = 0; i < rawIngredientList.size(); ++i){
    //     if(rawIngredientList.at(i) != '\'' && rawIngredientList.at(i) != ','){            
    //         ingredients.push_back(rawIngredientList.at(i));
    //     }
        
    //     if(rawIngredientList.at(i) == ',' || i == rawIngredientList.size() - 1){
    //         ++i;
    //         ingredientList.push_back(ingredients);
    //         ingredients.clear();
    //     }
    // }
}