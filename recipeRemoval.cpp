#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string extractIngredientFromRow(string row);
string getColumnInfo(string line, int targetColumn); //gets Column Info for any column except for 5th one
int jumpColumnIndex(string line, int targetColumn);
int endColumnIndex(string line, int targetColumn);
void fillVector(string data, vector<string>& cleanVector);
void sortCleanNER(vector<string>& cleanNER);
int findInVector(vector<string> search, string target);

int main(){
    ifstream inFS;
    inFS.open("recipes.csv");

    if(!inFS.is_open()){
        cout << "Error opepning file" << endl;
    }

    // Write a program that gives index of which index ingredient to delete
    // the index should be adjusted for deletion in mind

    string titleLine, recipeRow, ingredientRow, ingredient;
    vector<string> ingredientsFromRecipes;

    getline(inFS, titleLine);
    titleLine.clear();

    // Collect all ingreidnets in NER into ingredientsFromRecipes from recipes.csv
    while(getline(inFS, recipeRow)){
        vector<string> cleanNER;
        string rawNER = getColumnInfo(recipeRow, 4);
        fillVector(rawNER, cleanNER);

        for(int i = 0; i < cleanNER.size(); ++i){
            if(findInVector(ingredientsFromRecipes, cleanNER.at(i)) == -1){
                ingredientsFromRecipes.push_back(cleanNER.at(i));
            }
        }
    }

    inFS.close();

    sortCleanNER(ingredientsFromRecipes); // sort every character by alphabetical order
    cout << "ingredientsFromRecipes size: " << ingredientsFromRecipes.size() << endl;
    
    cout << endl;
    for(int i = 0; i < ingredientsFromRecipes.size(); ++i){
        cout << ingredientsFromRecipes.at(i) << endl;
    }

    // inFS.open("ingredients.csv");

    // if(!inFS.is_open()){
    //     cout << "Error opepning file" << endl;
    // }

    // getline(inFS, titleLine);
    // titleLine.clear();

    // int index = 2;
    // vector<int> invalidIngredientIndex;

    // // Collect all ingreidnets in NER into ingredientsFromRecipes
    // while(getline(inFS, recipeRow)){
    //     ingredient = extractIngredientFromRow(ingredientRow);
    //     if(findInVector(ingredientsFromRecipes, ingredient) == -1){
    //         invalidIngredientIndex.push_back(index - invalidIngredientIndex.size());
    //         cout << "Not found: " << ingredient << endl;
    //     }

    //     ++index;
    // }
    // inFS.close();

    return 0;
}


int findInVector(vector<string> search, string target){     // returns -1 if the target is not found in search
    int found = -1;
    for(int i = 0; i < search.size(); ++i){
        if(target == search.at(i)){
            found = 1;
        }
    }

    return found;
}

// Sort it alphabetically
void sortCleanNER(vector<string>& cleanNER){
    bool swapped;
    int n = cleanNER.size();

    do{
        swapped = false;
        for(int i = 0; i < n - 1; ++i){
            if(cleanNER.at(i) > cleanNER.at(i + 1)){
                string temp = cleanNER.at(i);
                cleanNER.at(i) = cleanNER.at(i + 1);
                cleanNER.at(i + 1) = temp;
                swapped = true;
            }
        }
        --n;
    }while(swapped);
}

string extractIngredientFromRow(string row){
    string ingredient;
    for(int i = 0; i < row.size(); ++i){
        if(row.at(i) != ','){
            ingredient.push_back(row.at(i));
        }
        else{
            break;
        }
    }

    return ingredient;
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