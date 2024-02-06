#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
// elements shared between sets
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  //set the intersection set
  std::set<T> intersect;
  //loop through one set, only add to intersect if value found in other set
  for(typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it){
    if(s2.find(*it) != s2.end()){
      intersect.insert(*it);
    }
  }
  return intersect;
  
}
template <typename T>
// elements in either set but no repeats
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  //set the unity set to one of the sets
  std::set<T> unity = s2;
  //only add elements from other set if they are NOT in unity already
  for(typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it){
    if(unity.find(*it) == unity.end()){
      unity.insert(*it);
    }
  }
  
  return unity;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
