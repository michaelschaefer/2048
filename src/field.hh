#ifndef __FIELD_HH__
#define __FIELD_HH__


// standard library includes
#include <iostream>


// namespace declarations
using namespace std;


/*
  CLASS FIELD
*/

class Field {
public:
  Field() : m_value(0) {}
  Field(unsigned int value) : m_value(value) {}
  inline void clear() { m_value = 0; }
  inline void fill(unsigned int value) { m_value = value; }
  inline unsigned int get_value() const { return m_value; }
  inline bool is_empty() const { return (m_value == 0); }

  unsigned int level_up() {
    m_value *= 2;
    return m_value;
  }

private:
  unsigned int m_value;
};

bool operator==(Field const& lhs, Field const& rhs) {
  return (lhs.get_value() == rhs.get_value());
}

ostream& operator<<(ostream& stream, const Field& field) {
  return (stream << field.get_value());
}


#endif // __FIELD_HH__

