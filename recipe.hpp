#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_

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
};


#endif