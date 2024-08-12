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
    string ingredientstring = "";
    string directionstring = "";

    cout << title << '|';

    // Display Ingredients
    for (int i = 0; i < ingredients.size(); ++i) {
        ingredientstring = ingredientstring + ingredients.at(i) + "@@";
    }
    cout << ingredientstring << '|';

    // Display Directions
    int step = 1;
    for (int i = 0; i < directions.size(); ++i) {
        directionstring = directionstring + "Step " + to_string(step++) + ": " + directions.at(i) + "~";
    }
    cout << directionstring << '|';

    // Display Carbon Footprint
    cout << carbon << " kg CO2" << '|';
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