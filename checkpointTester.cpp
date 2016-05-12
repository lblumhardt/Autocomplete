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
/*  Utils::load_dict(tst, input);
  cout << "inserting went fine \n"; 
  if(tst.find("if it was made")) {
    cout << "nice we found apple \n";
  }  
 */

  tst.insert("basketball", 5);
  tst.insert("asterisk", 10);
  tst.insert("basket", 1);
  tst.insert("barley", 5);
  tst.insert("back", 50000);
  tst.insert("application", 1);
  tst.insert("a", 1);
  tst.insert("app", 1);
  tst.insert("gugglebee", 1);

 // tst.insert("gypsie", 1);

  tst.insert("waldos", 1);
  tst.insert("are you not entertained", 1);
  tst.insert("never gonna give you up",1);
  
  tst.insert("basketballboy", 100);
  tst.insert("basketballboye", 5);
  tst.insert("basketballb", 199);

//guggle test
  tst.insert("glob", 1);



//ea test
  tst.insert("eas", 10);
  tst.insert("east", 90);
  tst.insert("easter", 50);
  tst.insert("ear", 1000);
  tst.insert("ears", 40);
  tst.insert("eat", 60);  
  //tst.insert("ea", 20);
  tst.insert("eastergorrilagram", 50000);

  tst.predictCompletions("ea", 2);
  //tst.predictCompletions("ba",2); 
  tst.predictCompletions("g", 100);
/*  tst.insert("a", 1);
  tst.insert("ab", 1);
  if(tst.insert("a", 1)) {
    cout << "reinsert a failed \n";
  }
  if(tst.insert("ab",1)) {
    cout << "reinsert ab failed \n";
  }
  //input.close();*/
  return 1;
}
