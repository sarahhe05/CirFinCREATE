#include <iostream>
#include <string>
#include <vector>
#include "recipe.hpp"

using namespace std;

recipe::recipe(){
    title = "";
    ingredients = {""};
    directions = {""};
    carbon = 1000;
}

recipe::recipe(string t, vector<string> i, vector<string> d, double c){
    title = t;
    ingredients = i;
    directions = d;
    carbon = c;
}

void recipe::display() const{
    cout << title << endl;
    cout << "Ingredients: " << endl;
    for(int i = 0; i < ingredients.size(); ++i){
        cout << "  " << ingredients.at(i) << endl; 
    }
    cout << endl;
    cout << "Directions: " << endl;
    for(int i = 0; i < directions.size(); ++i){
        cout << "  " << directions.at(i) << endl; 
    }
    cout << endl; 
}