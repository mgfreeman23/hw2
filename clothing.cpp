#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "clothing.h"
#include "util.h"

using namespace std;

// Clothing constructor
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product(category, name, price, qty){
  size_ = size;
  brand_ = brand;
}

// generate keyword set for clothing
std::set<std::string> Clothing::keywords() const{
  set<string> keywords;
  // parse brand and name to work as keywords
  keywords = parseStringToWords(brand_ + " " + name_);
  for(set<string>::iterator itr = keywords.begin(); itr != keywords.end(); ++itr){
    cout << *itr << endl;
  }
  return keywords;
}

//string containing product info
string Clothing::displayString() const{
  string display = name_ + "\n";
  display += "Size: " + size_ + " Brand: " + brand_  + "\n";
  display += to_string(price_) + " " + to_string(qty_) + " left.\n";
  return display;
}

void Clothing::dump(std::ostream& os) const{
  Product::dump(os);
  os << size_ << endl;
  os << brand_ << endl;
}