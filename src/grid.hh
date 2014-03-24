#ifndef __GRID_HH__
#define __GRID_HH__

#include <iostream>
#include <vector>

using namespace std;

enum LineDirection { FRONT = 1, BACK = 2 };
enum MoveDirection { LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };

class Pair {
public:
  Pair(unsigned int x, unsigned int y) : m_x(x), m_y(y) {}
  unsigned int& operator[] (unsigned int index) {
    if (index >= 1) {
      return m_y;
    }
    return m_x;
  }

private:
  unsigned int m_x, m_y;
};

class Field {
public:
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


class Line {  
public:  
  Line(vector<Field*>& data) : m_data(data) {}
  vector<Field*>& get_data() const { return m_data; }

  unsigned int merge(LineDirection direction, vector<Pair>& merges) {
    unsigned int n = m_data.size();
    unsigned int score = 0;
    Field* f = NULL;
    Field* g = NULL;

    if (direction == FRONT) {
      for (unsigned int i = 0; i < n-1; ++i) {
	f = m_data[i];
	if (f->is_empty()) {
	  continue;
	}

	g = m_data[i+1];
	if (f->get_value() == g->get_value()) {
	  score += f->level_up();
	  g->clear();
	  merges.push_back(Pair(i+1, i));
	}
      }
    } else {
      for (unsigned int i = n-1; i > 0; --i) {
	f = m_data[i];
	if (f->is_empty()) {
	  continue;
	}
	
	g = m_data[i-1];
	if (f->get_value() == g->get_value()) {
	  score += f->level_up();
	  g->clear();
	  merges.push_back(Pair(i-1, i));
	}
      }
    }

    return score;
  }

  vector<Pair> move(LineDirection direction) {
    vector<Pair> moves;
    unsigned int emptyFields = 0;
    unsigned int n = m_data.size();
    Field* f = NULL;

    if (direction == FRONT) {
      unsigned currentIndex = 0;
      vector<Field*>::iterator it_begin = m_data.begin();
      for (unsigned int i = 0; i < n; ++i) {
	f = m_data[currentIndex];
	if (f->is_empty()) {
	  emptyFields++;
	  m_data.push_back(*m_data.erase(it_begin + currentIndex));
	} else {
	  if (emptyFields > 0) {
	    moves.push_back(Pair(currentIndex + emptyFields, currentIndex));
	  }
	  currentIndex++;
	}
      }
    }
    return moves;
  }

private:
  vector<Field*>& m_data;
};

ostream& operator<<(ostream& stream, const Line& line) {
  vector<Field*>& data = line.get_data();
  vector<Field*>::iterator it = data.begin();
  while (true) {
    stream << *(*it);
    ++it;
    if (it == data.end()) {
      break;
    }
    stream << ", ";
  }
  return stream;
}



#endif // __GRID_HH__
