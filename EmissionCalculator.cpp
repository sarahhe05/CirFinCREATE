#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int endColumnIndex(string line, int targetColumn);
int jumpColumnIndex(string line, int targetColumn);
void fillIngredient(string rawIngredientListWithUnitAndAmnt, vector<string>& ingredientListWithUnitAndAmnt, string rawIngredientList, vector<string>& ingredientList);
double returnAmount(string ingredientWithUnitAndAmnt);
string returnUnit(string ingredientWithUnitAndAmnt, string ingredient);
void sortVectors(vector<string> const ingredientListWithUnitAndAmnt, vector<string>& ingredientList);
bool doesContain(string const inspection, string const target);
void sortVectorByStringsize(int i, vector<string>& ingredientList);

double returnCarbonAmount(double ingredientAmount, string unit, double Carbonamount){
    double recipeCarbonAmount = 0;

    vector<string> units = {"c.", "cup", "tsp.", "lb.", "qt.", "pt.", "Tbsp.", "oz.", "cups"};
    vector<double> conversionToKg = {
        0.236588,  // c. (assuming US cup)
        0.236588,  // cup (assuming US cup)
        0.00492892,  // tsp.
        0.453592,  // lb.
        0.946353,  // qt.
        0.473176,  // pt.
        0.0147868,  // Tbsp.
        0.0295735,  // oz.
        0.284131  // cups (assuming imperial cup)
    };

    for(int i = 0; i < units.size(); ++i){
        if(doesContain(unit, units.at(i))){
            cout << "INSIDE returnCarbonAmount" << endl;
            cout << ingredientAmount << endl;
            cout << Carbonamount << endl;
            cout << conversionToKg.at(i) << endl;
            recipeCarbonAmount = ingredientAmount *  Carbonamount * conversionToKg.at(i);
            cout << "OUTSIDE returnCarbonAmount" << endl;
        }
        else{
            recipeCarbonAmount = recipeCarbonAmount;
        }
    }

    return recipeCarbonAmount;
}

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

    string line, line2, rawIngredientListWithUnitAndAmnt, rawIngredientList, unit = "unitless";
    int recipeNum = 1;
    double amount, carbonamount = 0;
    vector<string> ingredientListWithUnitAndAmnt, ingredientList;
    vector<double> emissionOfEachRecipes;
    vector<int> oddRecipes;
    
    getline(inFS, line);     // we don't need the headers
    inFS.clear();

    while(getline(inFS, line)){
        double totalcarbonamount = 0;
        int nextIndex = jumpColumnIndex(line, 2);    // A function that returns the index of the start of a new column for ingredient column        
        int endIndex = endColumnIndex(line, 2);
        rawIngredientListWithUnitAndAmnt = line.substr(nextIndex, endIndex - nextIndex + 1);

        nextIndex = jumpColumnIndex(line, 4);       // Cross reference with column 4 to determine just the ingredient by name
        endIndex = endColumnIndex(line, 4);
        rawIngredientList = line.substr(nextIndex, endIndex - nextIndex + 1);

        fillIngredient(rawIngredientListWithUnitAndAmnt, ingredientListWithUnitAndAmnt, rawIngredientList, ingredientList);     // parse the strings into vectors of strings

        for(int i = 0; i < ingredientList.size(); ++i){
            amount = returnAmount(ingredientListWithUnitAndAmnt.at(i));
            unit = returnUnit(ingredientListWithUnitAndAmnt.at(i), ingredientList.at(i));        // Unit is defaulted to unitless and changes only when tempUnit returns something size > 0
            
            while(getline(enFS, line2)){
                if(doesContain(line2, ingredientList.at(i))){
                    cout << "Currently at: " << ingredientList.at(i) << endl;
                    for(int i = 0; i < line2.size();++i){
                         if(line2.at(i) == ','){
                             carbonamount = stoi(line2.substr(i + 1, line2.size() - 1));
                         } 
                    }
                    break;
                }
            }
            
            carbonamount = returnCarbonAmount(amount, unit, carbonamount);
            totalcarbonamount = totalcarbonamount + carbonamount;
        }
        cout << totalcarbonamount << endl;

        
        // for(int i = 0; i < ingredientList.size(); ++i){
        //     cout << ingredientList.at(i) << " | ";
        // }
        // cout << endl;
        // for(int i = 0; i < ingredientListWithUnitAndAmnt.size(); ++i){
        //     cout << ingredientListWithUnitAndAmnt.at(i) << " | ";
        // }
        // cout << endl;

        inFS.clear();
        ingredientListWithUnitAndAmnt.clear();
        ingredientList.clear();
        ++recipeNum;
    }

    inFS.close();
    enFS.close();

    // Write emission value into csv

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

void fillIngredient(string rawIngredientListWithUnitAndAmnt, vector<string>& ingredientListWithUnitAndAmnt, string rawIngredientList, vector<string>& ingredientList){
    string ingredients;
    // fill Ingredients for ingredientListWithUnitAndAmnt
    for(int i = 0; i < rawIngredientListWithUnitAndAmnt.size(); ++i){
        if(rawIngredientListWithUnitAndAmnt.at(i) != '\'' && rawIngredientListWithUnitAndAmnt.at(i) != ','){
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

    sortVectors(ingredientListWithUnitAndAmnt, ingredientList);
}

/*
A LIST OF ODD CASE
1. The ingredient list does not match amount of ingredients in NER
2. "1 fl oz or 3 cup of Salad Dressing" - double unit options
    - "1 (16 oz) box of Oranges"
3. "fl oz" - two worded units   // I 
4. Fractional numbers
5. Improper units "1 can of Chicken soup"
*/

// More edge cases       // ignoring case 1-3 (three digits, decimal, dash between #) here
// 4. cases like '1 13 cups salt'
// 5. 'chicken'

double returnAmount(string ingredientWithUnitAndAmnt){
    int integer = 1, numerator = 0, denominator = 1;
    int amountSize = 0;
    bool passedSpace = false;
    bool hasNum = false;

    for(int i = 0; i < ingredientWithUnitAndAmnt.size(); ++i){
        if(!isalpha(ingredientWithUnitAndAmnt.at(i)) && passedSpace == false){      // Counts # of chars before letter (likely unit) to determine if it's integer (size <= 3), fraction (size 4), mixed #s (size 6), or '1 13 cup' (size 4 w/o slash or 5)
            ++amountSize;
        }
        if(isalpha(ingredientWithUnitAndAmnt.at(i))){
            passedSpace = true;
        }
        if(isdigit(ingredientWithUnitAndAmnt.at(i)) && passedSpace == false){       // Determine if ingredientWithUnitAndAmnt has numeral => 'chicken' case or not
            hasNum = true;
        }
    }
    // We will try to read until space or slash or period
    // If space = likely integer or mixed # or '1 13 cups salt
    // Shave off decimal + three digit + dash...

    // To account for edge case 4, we will assume it's either size 4 ('1 2 cup') or size 5 ('1 13 cups'
    // To dstinguish size 4 fraction, we will simply see if it contain '/'

    if(hasNum){
        if(amountSize == 4){    
            if(doesContain(ingredientWithUnitAndAmnt, "/")){               // address "1/2 cup"
                numerator = stoi(ingredientWithUnitAndAmnt.substr(0, 1));
                denominator = stoi(ingredientWithUnitAndAmnt.substr(2, 1));
                integer = 0;
            }
            else{
                integer = stoi(ingredientWithUnitAndAmnt.substr(0, 1)) * stoi(ingredientWithUnitAndAmnt.substr(2, 1));  // Address "1 2 cup"
            }
        }
        else if(amountSize == 5){   // address "1 12 cup"
            integer = stoi(ingredientWithUnitAndAmnt.substr(0, 1)) * stoi(ingredientWithUnitAndAmnt.substr(2, 2));  // Address "1 2 cup"
        }
        else if((amountSize <= 3 && amountSize > 1 ) || amountSize == 6){
            integer = stoi(ingredientWithUnitAndAmnt.substr(0, 1));         // Address "2 cup" and "2 2/4 cup" 
            if(amountSize == 6){                                            // "2 2/4 cup" 
                numerator = stoi(ingredientWithUnitAndAmnt.substr(2, 1));   
                denominator = stoi(ingredientWithUnitAndAmnt.substr(4, 1));
            }
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

    if(amountSize == 2){
        unit = ingredientWithUnitAndAmnt.substr(2, fabs(ingredientWithUnitAndAmnt.size() - 2 - ingredient.size() - 1));
    }
    else if(amountSize == 4){ // '1 2 sugar'
        unit = ingredientWithUnitAndAmnt.substr(4, fabs(ingredientWithUnitAndAmnt.size() - 4 - ingredient.size() - 1));
    }
    else if(amountSize == 6){
        unit = ingredientWithUnitAndAmnt.substr(6, fabs(ingredientWithUnitAndAmnt.size() - 6 - ingredient.size() - 1));
    }

    return unit;
}

void sortVectorByStringsize(int i, vector<string>& ingredientList){ // i is the startIndex

    for(int j = i; j < ingredientList.size() - 1; ++j){
        for(int k = i; k < ingredientList.size() - j + i - 1; ++k){
            if(ingredientList.at(k).size() < ingredientList.at(k + 1).size()){
                string tempString = ingredientList.at(k);
                ingredientList.at(k) = ingredientList.at(k + 1);
                ingredientList.at(k + 1) = tempString;
            }
        }
    }
}

void sortVectors(vector<string> const ingredientListWithUnitAndAmnt, vector<string>& ingredientList){
    // determine if the entry shares the same ingredient between two vectors

    for(int i = 0; i < ingredientListWithUnitAndAmnt.size(); ++i){
        sortVectorByStringsize(i, ingredientList);
        for(int j = i; j < ingredientList.size(); ++j){
            if(doesContain(ingredientListWithUnitAndAmnt.at(i), ingredientList.at(j))){
                if(i != j){
                    string temp = ingredientList.at(i);
                    ingredientList.at(i) = ingredientList.at(j);
                    ingredientList.at(j) = temp;
                    // cout << "The two swapped: " << ingredientList.at(i) << " $and$ " << ingredientList.at(j) << endl;
                    // cout << "At index " << i << " of NER it is now: " << ingredientList.at(i) << endl; 
                    break;
                }
            }
        }
    }
    // Change ingredientList so it's in inner loop and ingredientListWithUnitAndAmnt...
    // Before you perform comparison and, you must always have to sort ingredientList by the great string size...starting at i
}

bool doesContain(string const inspection, string const target){
    bool doesContain = false;

    if(inspection.size() < target.size()){
        doesContain = false;
    }
    else{
        for(int i = 0; i < inspection.size() - target.size() + 1; ++i){
            // problem: contain accepts that butter is in peanut butter... (a contain issue)
            string checkString = inspection.substr(i, target.size());
            if(target == checkString){
                doesContain = true;
            }
        }
    }
    return doesContain;
}