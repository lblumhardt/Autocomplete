//#include "util.hpp"
#include "DictionaryHashtable.hpp"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word) {
  auto pair = hashtable.insert(word);
  return pair.second;

}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const {
  auto itr = hashtable.find(word);
  if(itr == hashtable.end()) {
    return false;
  }
  return true;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
