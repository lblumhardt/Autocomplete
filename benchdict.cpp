/* Lucas Blumhardt A12020745 */
#include "util.hpp"
#include "DictionaryTrie.hpp"
#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include <fstream>
#include <sstream>


int main(int argc, char *argv[]) {
  
  int n = 1000;
  if(argc != 5 ) {
    cout << "Wrong number of arguments! \n";
    return -1;
  }
  
  int min_size = atoi(argv[1]);
  int step_size = atoi(argv[2]);
  int num_iterations = atoi(argv[3]);
  
  std::filebuf fb;
  fb.open(argv[4], std::ios::in);
  std::istream input(&fb);
  Timer timer;
  cout << "DictionaryTrie \n";

  for(int i=0; i < num_iterations; i++) {
    DictionaryTrie mwt;
    Utils::load_dict(mwt, input, min_size + i*step_size);

    //average the lookup time between n worst-case lookups
    int averageTime = 0; 
    for(int j=0; j<n; j++) {
      timer.begin_timer();
      mwt.find("ofweiafj");
      mwt.find("izcndkj");
      mwt.find("powefijosij");
      mwt.find("ijfehfu");
      mwt.find("bbdjfbud");
      mwt.find("jjiewfe");
      mwt.find("ereorkj ad");
      mwt.find("qifjjad");
      mwt.find("zjioisf");
      mwt.find("asjfosidj");
      averageTime = averageTime + timer.end_timer();
    }
    averageTime = averageTime/n;  
    cout << min_size + i*step_size << "\t" << averageTime << "\n";
  }
  
  cout << "DictionaryBST \n";
  for(int i=0; i < num_iterations; i++) {
    DictionaryBST bst;
    Utils::load_dict(bst, input, min_size + i*step_size);

    //average the lookup time between n worst-case lookups
    int averageTime = 0; 
    for(int j=0; j<n; j++) {
      timer.begin_timer();
      bst.find("ofweiafj");
      bst.find("izcndkj");
      bst.find("powefijosij");
      bst.find("ijfehfu");
      bst.find("bbdjfbud");
      bst.find("jjiewfe");
      bst.find("ereorkj ad");
      bst.find("qifjjad");
      bst.find("zjioisf");
      bst.find("asjfosidj");
      averageTime = averageTime + timer.end_timer();
    }
    averageTime = averageTime/n; 
    cout << min_size + i*step_size << "\t" << averageTime << "\n";
  }

  cout << "DictionaryHashtable \n";
  for(int i=0; i < num_iterations; i++) {
    DictionaryHashtable ht;
    Utils::load_dict(ht, input, min_size + i*step_size);

    //average the lookup time between n worst-case lookups
    int averageTime = 0; 
    for(int j=0; j<n; j++) {
      timer.begin_timer();
      ht.find("ofweiafj");
      ht.find("izcndkj");
      ht.find("powefijosij");
      ht.find("ijfehfu");
      ht.find("bbdjfbud");
      ht.find("jjiewfe");
      ht.find("ereorkj ad");
      ht.find("qifjjad");
      ht.find("zjioisf");
      ht.find("asjfosidj");
      averageTime = averageTime + timer.end_timer();
    }
    averageTime = averageTime/n; 
    cout << min_size + i*step_size << "\t" << averageTime << "\n";
  }
  return 1;
}
