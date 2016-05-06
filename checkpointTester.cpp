//this is my tester file for the checkpoint lfggggg fuck my life forever
#include "DictionaryTrie.cpp"
#include "DictionaryHashtable.cpp"
#include "DictionaryBST.cpp"
#include "util.cpp"
#include <iostream>
#include <fstream>

int main() {
  std::filebuf fb;
  fb.open("myDict.txt", std::ios::in);
  std::istream input(&fb);
  DictionaryTrie tst;
  DictionaryHashtable hashtable; 
  Utils::load_dict(tst, input);
  
  //input.close();
  return 1;
}
