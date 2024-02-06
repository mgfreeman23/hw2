#include <iostream>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

#include "mydatastore.h"
#include "util.h"

using namespace std;

//implement destructor
MyDataStore::~MyDataStore(){
  //delete product pointers
  for (Product *p: products) {
    delete p;
  }
  products.clear();
  //delete user pointers, clear users map
  for(map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it){
    delete it->first;
  }
  users.clear();
  keyword_map.clear();
}

/**
 * Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p){

  //add to products and its keywords to map
  products.insert(p);
  //iterate through keywords of p
  for(string keyword: p->keywords()){
    //create new key in map if not one yet
    if(keyword_map.find(keyword) == keyword_map.end()){
      keyword_map[keyword] = std::set<Product *>();
    }
    //insert product corresponding to that keyword
    keyword_map[keyword].insert(p);
  }
}
/**
  * Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
  //add user and their initially empty cart to map
  vector<Product*> uservector;
  users.insert(make_pair(u, uservector));

}

/**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term, all products containing ALL search terms) while
  *  type 1 = OR search (union of results for each term, all products contain ANY search terms)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    
  //initialize data members
  set<Product*> resultSet;
  vector<Product*> resultVector;
  //in case of no search terms entered
  if(terms.size() == 0){
    return resultVector;
  }
  //convert vector of terms to set
  set<string> search_terms;
  for(string w : terms){
     search_terms.insert(w);
   }
  //iterate through search terms
  for(set<string>::iterator it = search_terms.begin(); it != search_terms.end(); ++it){
    //initialize resultSet
    if(resultSet.empty()){
      resultSet = keyword_map[*it];
    } else {
      //OR case: find union of products with keyword and products with other keywords
      if(type == 1){
        resultSet = setUnion(resultSet, keyword_map[*it]);
      } 
      //AND case: find intersection of products with keyword and products with other keywords
      else {
        resultSet = setIntersection(resultSet, keyword_map[*it]);
      }
    }
  }
  //convert results to vector form
  for(set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it){
    resultVector.push_back(*it);
  }
  return resultVector;
}

/**
  * Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile){
  //first line in file
  ofile << "<products>" << endl;
  //iterate through all the products and output to ofile
  for (Product *p: products) {
    p->dump(ofile);
  }
  //end of section
  ofile << "</products>" << endl;
  //user section
  ofile << "<users>" << endl;
  //iterate through and add all the users
  for(map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it){
    (it->first)->dump(ofile);
  }
  //end of user section
  ofile << "</users>" << endl;

}

// adds product to user's cart
void MyDataStore::addcart(string username, Product* prod){

  //find user corresponding to the username and add product to cart
  for(map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it){
    if((it->first)->getName() == username){
      (it->second).push_back(prod);
      return;
    }
  }
  //in this case there was no matching user
  cout << "Invalid request" << endl;
  return;
}

// print products in username's cart at current time
void MyDataStore::viewcart(string username){
   //find user corresponding to the username
  User* user = nullptr;
  vector<Product*> cart;
  for(map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it){
    if((it->first)->getName() == username){
      user = it->first;
      cart = it->second;
      break;
    }
  }
  //checks if no user with given username
  if(user == nullptr){
    cout << "Invalid username" << endl;
    return;
  }
  //loops through printing all cart items
  for(unsigned int i = 0; i < cart.size(); i++){
    cout << "Item " << i+1 << "\n" << cart[i]->displayString() << endl;
  }

}

// checks out the items in user's cart
void MyDataStore::buycart(string username){

  //find user corresponding to the username
  User* user = nullptr;
  vector<Product*> tempCart;

  for(map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it){
    if((it->first)->getName() == username){
      user = it->first;
      tempCart = it->second;
      break;
    }
  }
  //checks if no user with given username
  if(user == nullptr){
    cout << "Invalid username" << endl;
    return;
  }
  //set empty cart for remaining items
  vector<Product*> resultCart;
  //loops through cart items
  for(unsigned int i = 0; i < tempCart.size(); i++){
    //only buy and adjust user/product data members if available and enough $
    if(tempCart[i]->getQty() > 0 && tempCart[i]->getPrice() <= user->getBalance()){
      user->deductAmount(tempCart[i]->getPrice());
      tempCart[i]->subtractQty(1);
    } 
    // add not bought items to resulting cart
    else {
      resultCart.push_back(tempCart[i]);
    }
  }
  //find user in map and assign user's cart to the new cart vector
  for(map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it){
    if((it->first)->getName() == username){
      it->second = resultCart;
    }
  }
  return;
}