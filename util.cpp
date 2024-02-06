#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  //split at punctuation with at least two character words

  //initialize empty set for keywords
  set<string> keywords;
  //convert all words to lowercase
  string words = convToLower(rawWords);
  //get rid of extra spaces
  words = trim(words);
  //initialize index
  unsigned int i = 0;
  //iterate through characters of string
  while(i < words.size()){
    //initialize keyword
    string keyword = "";
    //keep adding until punctuation, space, or end of string
    while(!ispunct(words[i]) && !isspace(words[i]) && i < words.size()){
      keyword += words[i];
      i++;
    }
    //only add to keywords if 2 or more chars
    if(keyword.size() >= 2){
      keywords.insert(keyword);
    }
    i++;
  }
  return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
