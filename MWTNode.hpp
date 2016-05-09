#ifndef MWTNODE_HPP
#define MWTNODE_HPP
#include <vector>
using namespace std;

class MWTNode {

public:
  
  vector<MWTNode*> vec = vector<MWTNode*>(27, nullptr);
  unsigned char key;
  unsigned int freq;
  bool isword;
  int belowfreq;

  MWTNode();

 // bool operator<(const TSTNode& other);
private:
};

#endif // MWTNode_HPP
