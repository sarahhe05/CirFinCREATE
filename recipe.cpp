#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "recipe.h"

using namespace std;

recipe::recipe(){
    title = "";
    ingredients.push_back("");
    directions.push_back("");
    carbon = 1000;
}

recipe::recipe(string t, vector<string> i, vector<string> d, double c): title(t), ingredients(i), directions(d), carbon(c){}

void recipe::DisplayCarbon() const{
    cout << carbon;
}

void recipe::display() const{
    // cout << title << endl;
    // cout << "Ingredients: " << endl;
    // for(int i = 0; i < ingredients.size(); ++i){
    //     cout << "  " << ingredients.at(i) << endl; 
    // }
    // cout << endl;
    // cout << "Directions: " << endl;
    // for(int i = 0; i < directions.size(); ++i){
    //     cout << "  " << directions.at(i) << endl; 
    // }
    // cout << "Carbon amount: " << carbon << endl;
    // cout << endl; 
    cout << "*========================================*" << endl;
    cout << title << endl;
    cout << "*========================================*" << endl;

    // Display Ingredients
    cout << "\nIngredients:\n";
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < ingredients.size(); ++i) {
        cout << "| " << std::left << std::setw(40) << ingredients.at(i) << " |" << endl;
    }
    cout << "------------------------------------------" << endl;

    // Display Directions
    cout << "\nDirections:\n";
    cout << "------------------------------------------" << endl;
    int step = 1;
    for (int i = 0; i < directions.size(); ++i) {
        cout << "Step " << step++ << ": " << directions.at(i) << endl;
    }
    cout << "------------------------------------------" << endl;

    // Display Carbon Footprint
    cout << "\nCarbon Footprint: "  
         << carbon << " kg CO2" << endl;
    cout << "==========================================" << endl;
}
void recipe::setTitle(string t){
    title = t;
}
void recipe::setIngredients(vector<string> i){
    ingredients = i;
}
      
void recipe::setDirections(vector<string> d){
    directions = d;
}


void recipe::setCarbon(double c){
    carbon = c;
}