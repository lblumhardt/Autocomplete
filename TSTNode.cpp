#include "TSTNode.hpp"
#include <vector>
#include <set>

bool TSTNode::operator<(const TSTNode& other) {
  return this->key < other.key;
}
