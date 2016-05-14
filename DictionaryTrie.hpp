/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include "TSTNode.cpp"
//#include "MWTNode.hpp"

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
  class pairComp {
    
   public:

      bool operator()(std::pair<int,string> p1, std::pair<int, string> p2) const;
  };

  class MWTNode {

  public:
  
    vector<MWTNode*> vec = vector<MWTNode*>(27, (MWTNode*)0);
    MWTNode* parent;
    unsigned int freq;
    bool isword;
    bool visited;
    int belowfreq;
    int maxfreq;

    bool operator<(const MWTNode& other);

    MWTNode(int freq);
  };


  class pathsComp {
    public:
    
      bool operator()(std::pair<MWTNode*,std::string> p1, std::pair<MWTNode*,std::string> p2) const;
  };


  class potWordsComp {
    public:
      bool operator()(const std::pair<MWTNode*, std::string>& p1,const std::pair<MWTNode*, std::string>& p2) const;
/*
      bool operator()(std::pair<int,std::string> p1, std::pair<int,std::string> p2); */
  };




public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

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
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

  void deleteAll(MWTNode* curr);

  int maxBelowFreq(MWTNode* curr);

  unsigned char indexToChar(int index);

  void updateBelowFreq(MWTNode* curr);

  void updateMaxFreq(MWTNode* curr);
private:
  // Add your own data members and methods here
  //TSTNode* root;
  MWTNode* root;
};

#endif // DICTIONARY_TRIE_HPP
