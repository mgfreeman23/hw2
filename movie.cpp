#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "movie.h"
#include "util.h"

using namespace std;

// Movie constructor
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) : Product(category, name, price, qty){
  genre_ = genre;
  rating_ = rating;
}

// generate keyword set for Movie
std::set<std::string> Movie::keywords() const{
  set<string> keywords;
  // parse name to work as keyword
  keywords = parseStringToWords(name_);
  // user genre verbatim as keyword
  keywords.insert(convToLower(genre_));
  return keywords;
}

//string containing product info
string Movie::displayString() const{
  string display = name_ + "\n";
  display += "Genre: " + genre_ + " Rating: " + rating_  + "\n";
  display += to_string(price_) + " " + to_string(qty_) + " left.\n";
  return display;
}

//product info for database
void Movie::dump(std::ostream& os) const{
  Product::dump(os);
  os << genre_ << endl;
  os << rating_ << endl;
}