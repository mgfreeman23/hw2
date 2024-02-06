#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "product.h"

//implement keywords(), displayString(), and dump()

class Book : public Product {
  public:
    Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
  private:
    std::string isbn_;
    std::string author_;
};
