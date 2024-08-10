#ifndef _RECIPE_H_
#define _RECIPE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class recipe {
    private:
      string title;
      vector<string> ingredients;
      vector<string> directions;
      double carbon;
      
    public:
      recipe();
      recipe(string t, vector<string> i, vector<string> d, double c);
      void display() const;

      void setTitle(string t);
      void setIngredients(vector<string> i);
      void setDirections(vector<string> d);
      void setCarbon(double c);
};


#endif