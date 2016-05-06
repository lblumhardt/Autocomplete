#ifndef TSTNODE_HPP
#define TSTNODE_HPP

using namespace std;

class TSTNode {

public:
  TSTNode* left;
  TSTNode* center;
  TSTNode* right;
  unsigned char key;
  unsigned int freq;
  bool isword;
  int belowfreq;

  TSTNode(unsigned char key, unsigned int freq, TSTNode* left = 0, TSTNode* center = 0, TSTNode* right = 0, bool isword = false)
  : left(left), center(center), right(right), 
  key(key), freq(freq), isword(isword) {}

  bool operator<(const TSTNode& other);
private:
};

#endif // TSTNODE_HPP
