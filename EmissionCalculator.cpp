#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int endColumnIndex(string line, int targetColumn);
int jumpColumnIndex(string line, int targetColumn);
void fillIngredient(string rawIngredientListWithUnitAndAmnt, vector<string>& ingredientListWithUnitAndAmnt, string rawIngredientList, vector<string>& ingredientList);
double returnAmount(string ingredientWithUnitAndAmnt);
string returnUnit(string ingredientWithUnitAndAmnt, string ingredient);

int main(){
    
    ifstream inFS;                  // enable read file for recipes.csv / test.csv
    inFS.open("test.csv");

    if(!inFS.is_open()){            // check for potential open error
        cout << "test.csv cannot be opened" << endl;
        return 1;
    }

    ifstream enFS;                  // enable read file for ingredients.csv
    enFS.open("ingredients.csv");

    if(!enFS.is_open()){
        cout << "ingredients.csv cannot be opened" << endl;
        return 1;
    }

    string line, rawIngredientListWithUnitAndAmnt, rawIngredientList;
    string unit = "unitless";
    int recipeNum = 1;
    double amount;
    vector<string> ingredientListWithUnitAndAmnt, ingredientList;
    vector<double> emissionOfEachRecipes;
    vector<int> oddRecipes;
    
    getline(inFS, line);     // we don't need the headers
    inFS.clear();

    while(getline(inFS, line)){
        // A function that returns the index of the start of a new column for ingredient column        
        int nextIndex = jumpColumnIndex(line, 2);
        int endIndex = endColumnIndex(line, 2);
        rawIngredientListWithUnitAndAmnt = line.substr(nextIndex, endIndex - nextIndex + 1);

        // Cross reference with column 4 to determine just the ingredient by name
        nextIndex = jumpColumnIndex(line, 4);
        endIndex = endColumnIndex(line, 4);
        rawIngredientList = line.substr(nextIndex, endIndex - nextIndex + 1);

        fillIngredient(rawIngredientListWithUnitAndAmnt, ingredientListWithUnitAndAmnt, rawIngredientList, ingredientList);
        
        for(int i = 0; i < ingredientList.size(); ++i){
            // determine the unit and amount - we will assume the 1) first string of number before it hits the non "/" and nonspace is the amount, 2) everything else is unit
            // unit = returnUnit(ingredientListWithUnitAndAmnt.at(i) , ingredientList.at(i));
            amount = returnAmount(ingredientListWithUnitAndAmnt.at(i));
            
            // Unit is defaulted to unitless and changes only when tempUnit returns something size > 0
            unit = returnUnit(ingredientListWithUnitAndAmnt.at(i), ingredientList.at(i));
            cout << unit << endl;

            // call conversion if necessary
            // calculate and store into vector
        }

        // check for problem #1
        if(ingredientListWithUnitAndAmnt.size() != ingredientList.size()){
            oddRecipes.push_back(recipeNum);
        }

        inFS.clear();
        ingredientListWithUnitAndAmnt.clear();
        ingredientList.clear();
        ++recipeNum;
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

    inFS.close();
    enFS.close();

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

void fillIngredient(string rawIngredientListWithUnitAndAmnt, vector<string>& ingredientListWithUnitAndAmnt, string rawIngredientList, vector<string>& ingredientList){
    string ingredients;
    // fill Ingredients for ingredientListWithUnitAndAmnt
    for(int i = 0; i < rawIngredientListWithUnitAndAmnt.size(); ++i){
        if(rawIngredientListWithUnitAndAmnt.at(i) != '\"' && rawIngredientListWithUnitAndAmnt.at(i) != ','){
            ingredients.push_back(rawIngredientListWithUnitAndAmnt.at(i));
        }
        if(rawIngredientListWithUnitAndAmnt.at(i) == ',' || i == rawIngredientListWithUnitAndAmnt.size() - 1){
            if(ingredients.at(ingredients.size()-1) == 's'){    // change from plural to singular if applicable
                ingredients.pop_back();
            }
            ++i;
            ingredientListWithUnitAndAmnt.push_back(ingredients);
            ingredients.clear();
        }
    }

    // fill Ingredients for ingredientList
    for(int i = 0; i < rawIngredientList.size(); ++i){
        if(rawIngredientList.at(i) != '\'' && rawIngredientList.at(i) != ','){            
            ingredients.push_back(rawIngredientList.at(i));
        }
        
        if(rawIngredientList.at(i) == ',' || i == rawIngredientList.size() - 1){
            if(ingredients.at(ingredients.size()-1) == 's'){    // change from plural to singular if applicable
                ingredients.pop_back();
            }
            ++i;
            ingredientList.push_back(ingredients);
            ingredients.clear();
        }
    }
}

double returnAmount(string ingredientWithUnitAndAmnt){
    int integer = 0, numerator = 0, denominator = 1;
    int amountSize = 0;
    bool passedSpace = false;

    // Create a counting system to determine if it's integer(size 2), fraction(size 4), or mixed #s(size 6)
    for(int i = 0; i < ingredientWithUnitAndAmnt.size() && passedSpace == false; ++i){
        if(!isalpha(ingredientWithUnitAndAmnt.at(i))){
            ++amountSize;
        }
        else{
            passedSpace = true;
        }
    }

    if(amountSize == 4){
        numerator = stoi(ingredientWithUnitAndAmnt.substr(0, 1));
        denominator = stoi(ingredientWithUnitAndAmnt.substr(2, 1));
    }
    else if(amountSize == 2 || amountSize == 6){
        integer = stoi(ingredientWithUnitAndAmnt.substr(0, 1));
        if(amountSize == 6){
            numerator = stoi(ingredientWithUnitAndAmnt.substr(2, 1));
            denominator = stoi(ingredientWithUnitAndAmnt.substr(4, 1));
        }
    }

    return static_cast<double>(integer) + static_cast<double>(numerator)/static_cast<double>(denominator);
}

string returnUnit(string ingredientWithUnitAndAmnt, string ingredient){
    string unit;
    int amountSize = 0;
    bool passedSpace = false;

    // Create a counting system to determine if it's integer(size 2), fraction(size 4), or mixed #s(size 6)
    for(int i = 0; i < ingredientWithUnitAndAmnt.size() && passedSpace == false; ++i){
        if(!isalpha(ingredientWithUnitAndAmnt.at(i))){
            ++amountSize;
        }
        else{
            passedSpace = true;
        }
    }

    int startIndexOfIngredient = -1;
    for(int i = 0; i < ingredientWithUnitAndAmnt.size() - ingredient.size(); ++i){
        string checkString = ingredientWithUnitAndAmnt.substr(i, ingredient.size());
        if(checkString == ingredient){
           startIndexOfIngredient = i; 
        }
    }

    if(amountSize == 2){
        unit = ingredientWithUnitAndAmnt.substr(2, ingredientWithUnitAndAmnt.size() - 2 - ingredient.size() - 1);
    }
    else if(amountSize == 4){
        unit = ingredientWithUnitAndAmnt.substr(4, ingredientWithUnitAndAmnt.size() - 4 - ingredient.size() - 1);
    }
    else if(amountSize == 6){
        unit = ingredientWithUnitAndAmnt.substr(6, ingredientWithUnitAndAmnt.size() - 6 - ingredient.size() - 1);
    }

    return unit;
}