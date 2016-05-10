#include "MWTNode.hpp"
#include <set>

MWTNode::MWTNode(int freq) {
  vec = vector<MWTNode*>(27, (MWTNode*)0);
  for(int i = 0; i < 27; i++) {
    vec[i] = (MWTNode*)0;
  }
}
