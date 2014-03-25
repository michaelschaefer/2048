#ifndef __PAIR_HH__
#define __PAIR_HH__


// standard library includes
#include <iostream>


// namespace declarations
using namespace std;


class Pair {
public:
  Pair() : m_x(0), m_y(0) {}
  Pair(unsigned int x, unsigned int y) : m_x(x), m_y(y) {}

  unsigned int& operator[] (unsigned int index) {
    if (index >= 1) {
      return m_y;
    }
    return m_x;
  }

  bool operator== (Pair rhs) {
    if (m_x != rhs[0]) {
      return false;
    } else {
      return (m_y == rhs[1]);
    }
  }

  bool operator< (Pair rhs) {
    if (m_x < rhs[0]) {
      return true;
    } else if (m_x == rhs[0]) {
      return (m_y < rhs[1]);
    }
    return false;
  }

private:
  unsigned int m_x, m_y;
};

ostream& operator<<(ostream& stream, Pair& pair) {
  return (stream << "(" << pair[0] << ", " << pair[1] << ")");

}


#endif // __PAIR_HH__

