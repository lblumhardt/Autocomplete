#ifndef MWTNODE_HPP
#define MWTNODE_HPP
#include <vector>
using namespace std;

class MWTNode {

public:
  
  vector<MWTNode*> vec = vector<MWTNode*>(27, (MWTNode*)0);

  unsigned int freq;
  bool isword;
  int belowfreq;

  MWTNode(int freq);
/*
  for(int i = 0; i < 27; i++) {
    vec[i] = nullptr;
  }
*/


 // bool operator<(const TSTNode& other);
private:
};

#endif // MWTNode_HPP
