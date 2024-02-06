#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore{
  public:
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addcart(std::string username, Product* prod);
    void viewcart(std::string username);
    void buycart(std::string username);
  private:
  
    //mapping between users and their carts (e.g vector of products)
    std::map<User*, std::vector<Product*>> users;
    //set of the products
    std::set<Product *> products;
    //mapping between keyword and associated products
    std::map<std::string, std::set<Product*>> keyword_map;
};