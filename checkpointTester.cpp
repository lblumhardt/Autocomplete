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
 /* Utils::load_dict(tst, input);
  cout << "inserting went fine \n"; 
  if(tst.find("if it was made")) {
    cout << "nice we found apple \n";
  }  
 */
  tst.insert("basketball", 5);
  tst.insert("asterisk", 10);
  tst.insert("basket", 1);
  tst.insert("application", 1);
  tst.insert("a", 1);
  tst.insert("app", 1);
  tst.insert("gugglebee", 1);
  tst.insert("waldos", 1);
  tst.insert("are you not entertained", 1);
  tst.insert("never gonna give you up",1);
  
  if(tst.insert("basket", 50)){
    cout << "reinsert is still a problem \n";
  }
  //input.close();
  return 1;
}
