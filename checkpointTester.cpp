//this is my tester file for the checkpoint lfggggg fuck my life forever
#include "DictionaryTrie.cpp"
#include "DictionaryHashtable.cpp"
#include "DictionaryBST.cpp"
#include "util.cpp"
#include <iostream>
#include <fstream>

int main() {
  std::filebuf fb;
  fb.open("shuffled_freq_dict.txt", std::ios::in);
  std::istream input(&fb);
  DictionaryTrie tst;
  DictionaryHashtable hashtable; 
  DictionaryBST bst;
  Utils::load_dict(bst, input);
  cout << "inserting went fine \n"; 
  if(bst.find("if it was made")) {
    cout << "nice we found apple \n";
  }  
 
  //input.close();
  return 1;
}
