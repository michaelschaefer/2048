#ifndef __LINE_HH__
#define __LINE_HH__


// standard library include
#include <iostream>
#include <vector>


// project includes
#include "enums.hh"
#include "field.hh"
#include "pair.hh"


// namespace declaration
using namespace std;


/*
  CLASS LINE
*/

class Line {
public:
  Line(vector<Field> data) : m_data(data) {}
  vector<Field> get_data() const { return m_data; }

  unsigned int merge(LineDirection direction, vector<Pair>& merges) {
    unsigned int n = m_data.size();
    unsigned int score = 0;

    if (direction == FRONT) {
      for (unsigned int i = 0; i < n-1; ++i) {
	Field& f = m_data[i];
	if (f.is_empty()) {
	  continue;
	}

	Field& g = m_data[i+1];
	if (f.get_value() == g.get_value()) {
	  score += f.level_up();
	  g.clear();
	  merges.push_back(Pair(i+1, i));
	}
      }
    } else {
      for (unsigned int i = n-1; i > 0; --i) {
	Field& f = m_data[i];
	if (f.is_empty()) {
	  continue;
	}

	Field& g = m_data[i-1];
	if (f.get_value() == g.get_value()) {
	  score += f.level_up();
	  g.clear();
	  merges.push_back(Pair(i-1, i));
	}
      }
    }

    return score;
  }

  void move(LineDirection direction, vector<Pair>& moves) {
    unsigned int emptyFields = 0;
    unsigned int n = m_data.size();
    Field field;

    if (direction == FRONT) {
      unsigned int currentIndex = 0;
      vector<Field>::iterator it_begin = m_data.begin();
      for (unsigned int i = 0; i < n; ++i) {
	field = m_data[currentIndex];
	if (field.is_empty()) {
	  emptyFields++;
	  m_data.erase(it_begin + currentIndex);
	  m_data.push_back(field);
	} else {
	  if (emptyFields > 0) {
	    moves.push_back(Pair(currentIndex + emptyFields, currentIndex));
	  }
	  currentIndex++;
	}
      }
    } else {
      unsigned int currentIndex = n - 1;
      vector<Field>::iterator it_begin = m_data.begin();
      for (unsigned int i = 0; i < n; ++i) {
	field = m_data[currentIndex];
	if (field.is_empty()) {
	  emptyFields++;
	  m_data.erase(it_begin + currentIndex);
	  m_data.insert(it_begin, field);
	} else {
	  if (emptyFields > 0) {
	    moves.push_back(Pair(currentIndex - emptyFields, currentIndex));
	  }
	  currentIndex--;
	}
      }
    }
  }

private:
  vector<Field> m_data;
};

ostream& operator<<(ostream& stream, const Line& line) {
  vector<Field> data = line.get_data();
  vector<Field>::iterator it = data.begin();
  while (true) {
    stream << (*it);
    ++it;
    if (it == data.end()) {
      break;
    }
    stream << ",\t\t";
  }
  return stream;
}


#endif // __LINE_HH__

