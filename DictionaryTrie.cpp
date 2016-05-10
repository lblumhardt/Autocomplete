#include "util.hpp"
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() {
 // root = new TSTNode('?', 0, 0, 0, 0, false);
  root = nullptr;
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

  unsigned int i = 0;
  unsigned char temp;
  int index;
  //vector<MWTNode*> currvec;
  MWTNode* curr;
  //trying MWTrie now 
  if(root == nullptr) {
    root = new MWTNode(0);
    //cout << "root was null \n";
  }

  curr = root;
  if(!curr) {
    cout << "ERROR ROOT WAS STILL NULL \n";
  }
  
  while(i < word.length()) {
    
    temp = word[i];
    if(temp == 32) {
      index = 26;
    } 
    else {
      index = temp - 97;
    }
    if(curr->vec[index] == nullptr) {
      //cout << "pointer at index " << index << " was null \n";
      curr->vec[index] = new MWTNode(0);
      /*auto itr = currvec.begin();
      itr = itr + index;
      currvec.insert(itr, new MWTNode(0)); */
      curr = curr->vec[index];
      i++;
      continue;
     // i++; 
    }
    if(curr->vec[index] == nullptr) {
      //cout << "we shouldn't see this as often as the other \n";
    }
    else {
      //cout << "will was right! \n";
    }
    curr = curr->vec[index];
    i++; 
  } 
  if(curr->isword) {
    return false;
  }
  for(int j=0; j<27; j++) {
    if(root->vec[j] != nullptr) {
      //cout << j << " index was not nullptr \n";
    }
  }  
  curr->isword = true;
  curr->freq = freq;
  return true;
}
/* 
  curr = root;
  while(i < word.length()) {
    temp = word[i];

    if(temp == 32) {
      index = 26;
    }
    else {
      index = temp - 97;
    }  
    currvec = curr->vec;
    if(currvec[index] == nullptr) {
      cout << index << " we had a nullpointer here \n";
      currvec[index] = new MWTNode();
      curr = currvec[index];
    } 

    else {
      curr = currvec[index];
    }
    i++;
  } 
  if (curr->isword) {
    return false;
  }
  
  cout << "I assigned this node to true \n"; 
  curr->isword = true; 
  curr->freq = freq;  
  return true;

*/


/*  TSTNode* curr;
  unsigned int i = 0;
  //set the root while the dictionary is currently empty
  if(root->key == '?') {
    root = new TSTNode(word[i], 0, 0, 0, 0, false);
    cout << "assigned root to " << word[i] << " \n";
    curr = root;
    i++;
    while(i < word.length()) {
      curr->center = new TSTNode(word[i], 0, 0, 0, 0, false);
      cout << "appending " << word[i] << " to center root branch \n";
      curr = curr->center;
      i++;
    }
    curr->isword = true;
    curr->freq = freq;
    return true;
  }
  
  */ /* 
  //TSTNode* p;
  bool wasInserted = false;
  i = 0;
  curr = root;
  cout << "the root is still " << root->key << "\n";
  while(i < word.length()) {
    if(word[i] == curr->key){
      cout << "EQUALS!! curr->key is " << curr->key << " and word[i] is " << word[i] << "\n"; 
      //p = curr;
      i++;
      if(i >= word.length()) {
        break;
      }
      curr = curr->center;
     
      continue;
    }


    //if center pointer is null, insert downwards
    else if(curr->center == nullptr) {
      cout << "I thought center was null so i assigned " << word[i] << "to it \n";
      curr->center = new TSTNode(word[i], 0, 0, 0, 0, false);
      curr = curr->center;
      i++;
      wasInserted = true;
      continue;
    }
    //go to the right
    else if(curr->key < word[i]) {
      if(curr->right == nullptr) {
        cout << "I thought the right was null so i inserted " << word[i] << "to it \n";
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
        cout << "I thought the left was null so i inserted " << word[i] << "to it \n";
        curr->left = new TSTNode(word[i], 0, 0, 0, 0, false);
        i++;
        wasInserted = true;
      }
      curr = curr->left;
      continue;
    }

    //go down the center
    else if(word[i] == curr->key){
      cout << "EQUALS!! curr->key is " << curr->key << " and word[i] is " << word[i] << "\n"; 
      p = curr;
      i++;
      if(i >= word.length()) {
        break;
      }
      curr = curr->center;
     
      continue;
    }
    else if(curr->center == nullptr) {
      cout << "I thought center was null so i assigned " << word[i] << "to it \n";
      curr->center = new TSTNode(word[i], 0, 0, 0, 0, false);
      curr = curr->center;
      i++;
      wasInserted = true;
      continue;

    }*//*
  } 
  //cout << "p is " << p->key << "\n";
  //cout << "curr is " << curr->key << "\n";
  if(wasInserted == true) {
    curr->isword = true;
    cout << "was inserted was true so therefore true \n";
    curr->freq = freq;
    return true;
  }  
  if(curr->isword) {
    cout << "the prev node was a word and therefore insert returned false \n";
    return false;
  }
  cout << "the prev node wasn't a word and therefore insert returned true (basket) \n";
  curr->isword = true;
  curr->freq = freq;
  return true;




//retrying this fucking shit FUCK 

  bool inserted = false;
  i = 0;
  curr = root;
  while(i < word.length()) {
    if(word[i] == curr->key && curr->center != nullptr) {
      i++;
      if(i >= word.length()) {
        break;
      }
     
      curr = curr->center;
    }

    else if(curr->center == nullptr) {
      cout << "center is null, assigned " << word[i] << "to it \n";
      curr->center = new TSTNode(word[i], 0, 0, 0, 0, false);
      curr = curr->center;
      i++;
      inserted = true;
    }

    else if(curr->key < word[i]) {
      if(curr->right == nullptr) {
        cout << "right is null, assigned " << word[i] << "to it \n";
        curr->right = new TSTNode(word[i], 0, 0, 0, 0, false);
        i++;
        inserted = true;       
      }
      curr = curr->right;
    }

    else if(word[i] < curr->key) {
      if(curr->left == nullptr) {
        cout << "left is null, assigned " << word[i] << "to it \n";
        curr->left = new TSTNode(word[i], 0, 0, 0, 0, false);
        i++;
        inserted = true;
      }
      curr = curr->left;
    }
  }
  if(inserted || curr->isword == false) {
    curr->isword = true;
    curr->freq = freq;
    return true;
  }
  return false;
*/
 // return recursiveInsert(word, freq, root);


bool DictionaryTrie::recursiveInsert(std::string word, unsigned int freq, TSTNode* root) {

  return true;
  /* if(root == nullptr) {
    unsigned int i = 0;
    TSTNode* curr;
    root = new TSTNode(word[i], 0, 0, 0, 0, false);
    cout << "assigned root to " << word[i] << " \n";
    curr = root;
    i++;
    while(i < word.length()) {
      curr->center = new TSTNode(word[i], 0, 0, 0, 0, false);
      cout << "appending " << word[i] << " to center root branch \n";
      curr = curr->center;
      i++;
    }
    curr->isword = true;
    curr->freq = freq;
    return true;
  }

  if(root->key < word.front()) {
    recursiveInsert(word, freq, root->right);
  }
  
  else if(word.front() < root->key) {
    recursiveInsert(word, freq, root->left);
  }

  else {
    word.erase(0, 1);
    if(word != ""){
      recursiveInsert(word, freq, root->center);
    }
    else {
      root->isword = true;
      root->freq = freq;
      return true;
    }
  }
  return false; */
}
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  unsigned int i = 0;
  unsigned char temp;
  int index;
  MWTNode* curr = root;
  vector<MWTNode*> currvec;
  if(root == nullptr) {
    return false;
  }

  while(i < word.length()) {
    temp = word[i];
    if(temp == 32) {
      index = 26;
    }
    else {
      index = temp - 97;
    }
    
    currvec = curr->vec;
    if(currvec[index] == nullptr) {
      return false;
    }
    curr = currvec[index];
    i++;
  }  
  if(curr->isword) {
    return true;
  }
  return false;
/*
  TSTNode* curr = root;
  unsigned int i = 0;
  while(i < word.length()) {
    if(curr == nullptr) {
      return false;
    }
    else if(curr->key < word[i]) {
      curr = curr->right;
    }
    else if(word[i] < curr->key) {
      curr = curr->left;
    }
    else {
      curr = curr->center;
      i++;
    }
  }
  return curr->isword; */

  
}

void DictionaryTrie::deleteAll(MWTNode* curr) {
  if(curr == nullptr) {
    return;
  }
  for(int i = 0; i < 27; i++) {
    deleteAll(curr->vec[i]);
  }
  delete curr;
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
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}
