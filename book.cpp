#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "book.h"
#include "util.h"

using namespace std;

// Book constructor
Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : Product(category, name, price, qty){
  isbn_ = isbn;
  author_ = author;

}

// generate keyword set for book
std::set<std::string> Book::keywords() const{
  set<string> keywords;
  // parse author and name to work as keywords
  keywords = parseStringToWords(author_ + " " + name_);
  // use isbn number verbatim as keyword
  keywords.insert(isbn_);
  return keywords;
}

//string containing product info
string Book::displayString() const{
  string display = name_ + "\n";
  display += "Author: " + author_ + " ISBN: " + isbn_  + "\n";
  display += to_string(price_) + " " + to_string(qty_) + " left.\n";
  return display;
}

//outputs to database the product info
void Book::dump(std::ostream& os) const{
  Product::dump(os);
  os << isbn_ << endl;
  os << author_ << endl;
}
