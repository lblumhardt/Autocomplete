/*Lucas Blumhardt A12020745
 * This is a Multiway Trie that holds words inserted into it from a dictionary
 * */
#include "DictionaryTrie.hpp"
#include <set>
#include <stack>
#include <algorithm>
#include <iterator>
#include <queue>
#include <utility>

//comparator used by potWords2 in predictCompletions
bool DictionaryTrie::pairComp::operator()(std::pair<int,string> p1, std::pair<int, string> p2) const{
  int p1freq = p1.first;
  int p2freq = p2.first;
  return p1freq > p2freq;
}


bool DictionaryTrie::MWTNode::operator<(const MWTNode& other) {
  return freq > other.freq;
}

//Multiway Trie Node class
DictionaryTrie::MWTNode::MWTNode(int freq){
    for(int i=0; i<27; i++) {
      vec[i] = (MWTNode*)0;
    }
    parent = nullptr;
    freq = 0;
    belowfreq = 0;
    maxfreq = 0;
    visited = false;
  }

//comparator used by potWords
bool DictionaryTrie::potWordsComp::operator()(const std::pair<MWTNode*, std::string>& p1,const std::pair<MWTNode*, std::string>& p2) const {
  return p1.first->freq < p2.first->freq;
}

bool DictionaryTrie::pathsComp::operator()(std::pair<MWTNode*,std::string> p1, std::pair<MWTNode*,std::string> p2) const{
  return p1.first->maxfreq > p2.first->maxfreq;
} 


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() {
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
  MWTNode* curr;
  if(root == nullptr) {
    root = new MWTNode(0);
  }
  curr = root; 
  while(i < word.length()) {
    
    temp = word[i];
    if(temp == 32) {
      index = 26;
    } 
    else {
      index = temp - 97;
    }
    if(curr->vec[index] == nullptr) {
      curr->vec[index] = new MWTNode(0);
      curr->vec[index]->parent = curr;
      curr->vec[index]->freq = 0;
      curr->vec[index]->maxfreq = 0;
      curr->vec[index]->belowfreq = freq;
      curr = curr->vec[index];
      i++;
      continue;
    }
    curr = curr->vec[index];
    i++; 
  } 
  if(curr->isword) {
    return false;
  }

  curr->isword = true;
  curr->freq = freq;
  updateMaxFreq(curr);
  return true; 
}


/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  unsigned int i = 0;
  unsigned char temp;
  int index;
  MWTNode* curr = root; 
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
    
    if(curr->vec[index] == nullptr) {
      return false;
    }
    curr = curr->vec[index];
    i++;
  }  
  if(curr->isword) {
    return true;
  }
  return false;
}

//recursive helper to delete all nodes
void DictionaryTrie::deleteAll(MWTNode* curr) {
  if(curr == nullptr) {
    return;
  }
  for(int i = 0; i < 27; i++) {
    deleteAll(curr->vec[i]);
  }
  delete curr;
}

//helper I abandoned
void DictionaryTrie::updateBelowFreq(MWTNode* curr) {
  int max = curr->belowfreq;
  for(int i = 0; i < 27; i++) {
    if(curr->vec[i] != nullptr) {
      if(max < curr->vec[i]->belowfreq) {
        max = curr->vec[i]->belowfreq;
      }
    }
  }
  while(curr->parent != nullptr) {
    if(curr->belowfreq < max) {
      curr->belowfreq = max;
      curr = curr->parent;
    }
    else { break; }
  }
}

//helper I abandoned
void DictionaryTrie::updateMaxFreq(MWTNode* curr) {
  int max = 0;
  for(int i=0; i<27; i++) {
    if(curr->vec[i] != nullptr) {
      if(curr->vec[i]->freq < curr->vec[i]->maxfreq) {
        if(max < curr->vec[i]->maxfreq) {
          max = curr->vec[i]->maxfreq;
        }
      }
      else {
        if(max < curr->vec[i]->freq) {
          max = curr->vec[i]->freq;
        }
      }
    }
  }
  curr->maxfreq = max;
  if(curr->freq > max) {
    max = curr->freq;
  }
  curr = curr->parent;
  while(curr->parent != nullptr) {
    if(curr->maxfreq < max) {
      curr->maxfreq = max;
      curr = curr->parent;
    }
    else { break; }
  }

}

//helper I abandoned
//returns the maximum frequency of any word this node is a prefix of, including itself 
//(if it is a word)
int DictionaryTrie::maxBelowFreq(MWTNode* curr){
 
  bool leaf = true;
  int max = curr->freq;
  for(int i = 0; i < 27; i++) {
    if(curr->vec[i] != nullptr) {
      leaf = false;
      if(max < curr->vec[i]->belowfreq) {
        max = curr->vec[i]->belowfreq;
      }
    }
  }
  if(leaf) {
    curr->belowfreq = max;
  }
  
  while(curr->parent != nullptr) {
    if(curr->belowfreq < max) {
      curr->belowfreq = max;
      curr = curr->parent;
    }
    else { break; }
  }
  
  return max;
}

//helper method to take vec's index and represent it as a-z
unsigned char DictionaryTrie::indexToChar(int index) {
  if(index == 26) {
    return (unsigned char)32;
  }
  return (unsigned char)index + 97;
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
  std::string currstring = prefix;
  
  //verifying args
  if(num_completions <= 0) {
    return words;
  }  
  int limit = num_completions;
  unsigned int i = 0;
  MWTNode* curr = root;
  unsigned int index; 
  unsigned char temp;
  int max;  
  int words_stored = 0;
  //Finding prefix node
  while(i < prefix.length()) {
    temp = prefix[i]; 
    if(temp == 32) {
      index = 26;
    } 
    else {
      index = temp - 97;
    }
    
    if(curr->vec[index]) {
      curr = curr->vec[index];
    } 
    else {
      cout << "Invalid prefix for this dictionary \n";
      return std::vector<std::string>(0,""); 
    }
    i++;
  }
  MWTNode* prefixNode = curr; 
  //std::priority_queue<MWTNode*, std::vector<MWTNode*>, potWordsComp> pq;

/*  std::priority_queue<std::pair<int,string>, std::vector<std::pair<int, string>>, pairComp> potWords2;
  max = curr->maxfreq;
  std::stack<std::pair<MWTNode*,std::string>> toCheck;
  bool aInserted = false;
  //check if prefix is one of the most frequent words
  if(curr->isword) {
    words_stored++;
    potWords2.push(std::make_pair(curr->freq, prefix));
  }

  //add prefix node's children to the stack 
  for(int i=0; i < 27; i++) {
    if(curr->vec[i] != nullptr) {
      currstring = prefix;
      currstring += indexToChar(i);
      toCheck.push(std::make_pair(curr->vec[i], currstring));
    }
  }
  
  //go through the stack
  currstring = prefix;  
  std::pair<MWTNode*, std::string> currPair;
  while(!toCheck.empty()) {
    currPair = toCheck.top();
    if(currPair.first->visited == false) {
      toCheck.pop();  
      //add current node's children to the stack
      for(int i=0; i < 27; i++) {
        if(currPair.first->vec[i] != nullptr) {
          currstring = currPair.second;
          currstring += indexToChar(i);
          toCheck.push(std::make_pair(currPair.first->vec[i],currstring));
        }
      }
      //check if current node is a word to put into the max heap
      if(currPair.first->isword) { 
        words_stored++;
        potWords2.push(std::make_pair(currPair.first->freq, currPair.second));
      }
      currPair.first->visited = true;
    }
  }

  //take the top num_completion words out of the heap
  for(int i=0; i < num_completions; i++) {
    if(!potWords2.empty()) {
      words.push_back(potWords2.top().second);
      potWords2.pop();
    }
    else { break; }
  }
  return words;
*/
/*
This is the algorithm Charles taught in a tutor sesh. Or at least close to it. i thought I implemented
his alg. exactly, but there were things I couldn't debug. I changed the alg. little by little until I 
completely abandoned it. I decided just to go with a naive solution to earn more than 0 points, however
after two days of debugging I can't figure out what's wrong with my solution anyway.
*/ 
  //pq holds the potential Words. it's a min heap of frequencies
  std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, pairComp> potWords;

  //double pq of the potential pathways to the nodes. it's a min/max heap 
  //of frequencies
  std::multiset<std::pair<MWTNode*, std::string>, pathsComp> paths;
  
  //trying it on vector
  //std::vector<std::pair<MWTNode*, std::string>, pathsComp> pathvec;

  //check if the prefix is a word
  //cout << "checking if prefix is a word \n";
  if(curr->isword) {
    if(curr->maxfreq < curr->freq) {
      //cout << "putting the prefix in potwords too \n";
      potWords.push(std::make_pair(curr->freq, prefix));
      limit--;
      if(limit == 0) {
        words.push_back(currstring);
        return words;       
      }
    }
    else { 
      //cout << "putting the prefix in potwords too \n";
      potWords.push(std::make_pair(curr->freq, prefix));
    }
  }
  
  unsigned char tempChar;
 
  std::pair<MWTNode*, std::string> tempPathPair;  
  std::pair<int, std::string> tempPotWordsPair;

  //check if prefix node has children to explore
  //cout << "checking if prefix has children \n";
  for(int i=0; i < 27; i++) {
    if(curr->vec[i] != nullptr) {
      tempChar = indexToChar(i);
      currstring = prefix;
      currstring += tempChar;
      
    
      //if the child is a leaf node, add to potential words (could be optimized)
      if(curr->vec[i]->maxfreq == 0) {
        potWords.push(std::make_pair(curr->vec[i]->freq, currstring));
        continue;
      }
      else {
        //cout << "im inserting " << currstring  << " into paths \n";
        auto pear = paths.insert(std::make_pair(curr->vec[i], currstring));
        //cout << "inserted and paths size is now: " << paths.size() << "\n";
      }     
    }  
  }

  //remove minimum values while size is greater than limit
  while(paths.size() > limit) {
    auto deleteitr = paths.end();
    deleteitr--;
    //cout << "im deleting an item from paths \n";
    paths.erase(deleteitr);  
  }
   
  //remove min values from potWords while size is greater than num_completions
  while(potWords.size() > num_completions) {
    potWords.pop();
  }

  bool firstMaxFound = false;

  MWTNode* p;
  MWTNode* tempNode;
 
  //exploring all the paths
  while(!paths.empty()) {
    if(limit == 0) {
      break;
    }
    //if the smallest freq in potWords is greater than the largest freq in
    //paths, we have all the words we need and can break
    //WARNING IM NOT SURE if we WILL have enough words??????? 
    if(potWords.empty()) {
      //hi :^)
    }
    else if(potWords.top().first > (*paths.begin()).first->maxfreq) {
      if(potWords.size() >= num_completions) { 
        if(firstMaxFound) {
          break;
        }
      }
    }    

    tempPathPair = *(paths.begin());
    paths.erase(paths.begin());
    p = tempPathPair.first;
    currstring = tempPathPair.second;

    //check if p is a word
      if(p->isword) {
        if(potWords.size() < num_completions) {
          potWords.push(std::make_pair(p->freq, currstring));
        }
        else {
          tempPotWordsPair = potWords.top();
          if(p->freq == max) {
            firstMaxFound = true;
            potWords.push(std::make_pair(p->freq, currstring));
            limit--;
            if(limit == 0) {
              break;
            }
            auto tempPathPair2 = *(paths.begin());
            max = tempPathPair2.first->maxfreq;
          }
          //if this node's frequency is greater than the smallest freq in potWords
          else if(p->freq > tempPotWordsPair.first) {
            potWords.pop();
            potWords.push(std::make_pair(p->freq, currstring));
          }
        }
      }

    //for every child in this node
    for(int i=0; i < 27; i++) {
      //ignore null children
      if(p->vec[i] == nullptr) {
        continue;
      }
      tempChar = indexToChar(i);
      currstring += tempChar;

      //is this node an expandable path?
      if(p->vec[i]->maxfreq != 0) {
        if(paths.size() >= limit) {
          auto backitr = paths.end();
          backitr--;          
          auto smallpair = *backitr;
          if(p->vec[i]->maxfreq > (smallpair.first)->maxfreq) {
            //cout << "im deleting an item from paths \n";
            paths.erase(backitr);  
            //cout << "i'm inserting " << currstring << " into paths \n";
            paths.insert(std::make_pair(p->vec[i], currstring));
          }
        }
        else { 
          //cout << "inserting " << currstring << " into paths\n";
          paths.insert(std::make_pair(p->vec[i], currstring));
        }
      }
      else {
        potWords.push(std::make_pair(p->vec[i]->freq, currstring));
      }
      while(potWords.size() > num_completions) {
        potWords.pop();
      }
      currstring.pop_back(); 
    }
  }

  std::vector<string> holder;
  i = 0;
  while(i < num_completions && potWords.empty() != true) {
    holder.push_back(potWords.top().second);
    potWords.pop();
    i++;
  }  
  std::reverse(holder.begin(), holder.end()); 
  return holder;




/* Deal with this later. this currently returns THE max word regardless of what 
 * num_completions is. Uncomment this if it's thursday at 11:50 and you're 
 * scared of failing. gonna try the charles-algorithm above 
 
  //this priority queue holds the belowfreq, and index in which its located
  std::priority_queue<std::pair<int,int>, std::vector<pair<int,int>>, pairComp> potWords;
  std::pair<int,int> currMax;
  std::string currWord = prefix;
  int wordsFound = 0;
 
  //this whole while loop needs some help. push the first 27 vector
  //then push the 27 - 1 vector that held the max, etc. 
  //maybe a for loop, from 0 to num_completions

  while(curr) {
    for(int i=0; i < 27; i++) {
      if(curr->vec[i]) {
        //cout << "curr->vec[" << (unsigned char)(i+97) << "]->belowfreq is " << curr->vec[i]->belowfreq << " \n";
        std::pair<int,int> p (curr->vec[i]->belowfreq, i);
        potWords.push(p);
      }
    }
    currMax = potWords.top();
    potWords.pop();
    temp = indexToChar(currMax.second);
    currWord += temp;
    curr = curr->vec[currMax.second];
    
    if(currMax.first == (int)curr->freq) {
      //we found the max freq
      words.push_back(currWord);
      wordsFound++;
      //method only returns one word
      cout << "added a word to the list: " << currWord << "\n";
      return words;
      //if(wordsFound == num_completions) {
        //break;
      //}      

    } 
  }
*/  
 // return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}
