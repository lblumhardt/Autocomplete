#include "util.hpp"
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() {

}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  //check if string is empty
  if(word == "") {
    cout << "attempting to insert an empty string. Returning false \n";
    return false;
  }
  TSTNode* curr;
  unsigned int i = 0;
  //set the root while the dictionary is currently empty
  if(root == nullptr) {
    root = new TSTNode(word[i], 0, 0, 0, 0, false);
    curr = root;
    i++;
    while(i < word.length()) {
      curr->center = new TSTNode(word[i], 0, 0, 0, 0, false);
      curr = curr->center;
    }
    curr->isword = true;
    curr->freq = freq;
    return true;
  }
  
  

  bool wasInserted = false;
  i = 0;
  curr = root;
  while(i < word.length()) {
    //if center pointer is null, insert downwards
    if(curr->center == nullptr) {
      curr->center = new TSTNode(word[i], 0, 0, 0, 0, false);
      curr = curr->center;
      i++;
      wasInserted = true;
      continue;
    }

    //go to the right
    else if(curr->key < word[i]) {
      if(curr->right == nullptr) {
        curr->right = new TSTNode(word[i], 0, 0, 0, 0, false); 
        i++; 
        wasInserted = true;   
      }
      curr = curr->right;
      continue;
    }

    //go to the left
    else if(word[i] < curr->key) {
      if(curr->left == nullptr) {
        curr->left = new TSTNode(word[i], 0, 0, 0, 0, false);
        i++;
        wasInserted = true;
      }
      curr = curr->left;
      continue;
    }

    //go down the center
    else {
      curr = curr->center;
      i++;
      continue;
    }
  } 
  if(wasInserted == true) {
    curr->isword = true;
    curr->freq = freq;
    return true;
  } 
  return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
