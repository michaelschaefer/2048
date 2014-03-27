#ifndef __GRID_HH__
#define __GRID_HH__


// standard library includes
#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <vector>

// project includes
#include "enums.hh"
#include "field.hh"
#include "line.hh"
#include "pair.hh"


// namespace declarations
using namespace std;


class Grid {
public:
  Grid(unsigned int size) : m_size(size) {
    this->initialize(0);
  }

  unsigned int fill_fields(unsigned int n_fields, unsigned int value) {
    list<Pair>::iterator iterator;
    unsigned int index = 0, inserted_fields = 0;

    // init random generator
    srand(time(NULL));

    for (unsigned int i = 0; i < n_fields; ++i) {
      if (m_empty_fields.empty()) {
	break;
      }

      // move iterator to random free field
      index = rand() % m_empty_fields.size();
      iterator = m_empty_fields.begin();
      advance(iterator, index);

      // fill field and remove it from m_empty_fields
      Pair coordinatePair = *iterator;
      m_fields[coordinatePair[0]][coordinatePair[1]].fill(value);
      m_empty_fields.remove(*iterator);
      inserted_fields++;
    }

    return inserted_fields;
  }

  list<Pair> get_empty_fields() { return m_empty_fields; }

  vector<vector<Field> > get_fields() { return m_fields; }

  vector<Field> get_line(unsigned int index, LineOrientation orientation) const {
    if (index >= m_size) {
      index = m_size - 1;
    }

    if (orientation == ROW) {
      return m_fields[index];
    } else {
      vector<Field> column;
      for (unsigned int i = 0; i < m_size; ++i) {
	column.push_back(m_fields[i][index]);
      }
      return column;
    }
  }

  unsigned int get_size() const { return m_size; }

  bool is_locked() {
    if (m_empty_fields.empty() == false) {
      return false;
    }

    for (unsigned int i = 0; i < m_size; ++i) {
      for (unsigned int j = 0; j < m_size-1; ++j) {
	if (m_fields[i][j].get_value() == m_fields[i][j+1].get_value()) {
	  return false;
	}
	if (m_fields[j][i].get_value() == m_fields[j+1][i].get_value()) {
	  return false;
	}
      }
    }

    return true;
  }

  unsigned int merge(MoveDirection direction, vector<Pair>& merges) {
    LineOrientation orientation;
    unsigned int score = 0;

    if (direction == LEFT || direction == RIGHT) {
      orientation = ROW;
    } else {
      orientation = COLUMN;
    }

    for (unsigned int i = 0; i < m_size; ++i) {
      // get row of column to merge
      Line line(this->get_line(i, orientation));
      
      // do merge and update score
      vector<Pair> merges_on_current_line;
      if (direction == LEFT || direction == UP) {
	score += line.merge(FRONT, merges_on_current_line);
      } else {
	score += line.merge(BACK, merges_on_current_line);
      }

      // build merge list
      unsigned int n = merges_on_current_line.size();
      for (unsigned int j = 0; j < n; ++j) {
	Pair pair = merges_on_current_line[j];
	if (orientation == ROW) {
	  merges.push_back(Pair(i, pair[0]));
	  merges.push_back(Pair(i, pair[1]));
	  m_empty_fields.push_back(Pair(i, pair[0]));
	} else {
	  merges.push_back(Pair(pair[0], 1));
	  merges.push_back(Pair(pair[1], 1));
	  m_empty_fields.push_back(Pair(pair[0], i));
	}
      }

      // overwrite changes
      this->overwrite(i, orientation, line.get_data());
    }

    m_empty_fields.sort();
    return score;
  }

  void move(MoveDirection direction, vector<Pair>& moves) {
    LineOrientation orientation;

    if (direction == LEFT || direction == RIGHT) {
      orientation = ROW;
    } else {
      orientation = COLUMN;
    }

    for (unsigned int i = 0; i < m_size; ++i) {
      // get row or column to move
      Line line(this->get_line(i, orientation));

      // move current line
      vector<Pair> moves_on_current_line;
      if (direction == LEFT || direction == UP) {
	line.move(FRONT, moves_on_current_line);
      } else {
	line.move(BACK, moves_on_current_line);
      }

      // build move list
      unsigned int n = moves_on_current_line.size();
      for (unsigned int j = 0; j < n; ++j) {
	Pair pair = moves_on_current_line[j];
	Pair from, to;
	if (orientation == ROW) {
	  from = Pair(i, pair[0]);
	  to = Pair(i, pair[1]);
	} else {
	  from = Pair(pair[0], i);
	  to = Pair(pair[1], i);
	}
	moves.push_back(from);
	moves.push_back(to);
	m_empty_fields.remove(to);
	m_empty_fields.push_back(from);
      }

      // overwrite changes
      this->overwrite(i, orientation, line.get_data());
    }

    m_empty_fields.sort();
  }

private:
  void initialize(unsigned int value) {
    for (unsigned int i = 0; i < m_size; ++i) {
      m_fields.push_back(vector<Field>());
      for (unsigned int j = 0; j < m_size; ++j) {
	m_fields[i].push_back(Field(value));
	m_empty_fields.push_back(Pair(i, j));
      }
    }
  }

  void overwrite(unsigned int index, LineOrientation orientation, vector<Field> data) {
    if (index >= m_size || data.size() < m_size) {
      return;
    }

    for (unsigned int i = 0; i < m_size; ++i) {
      if (orientation == ROW) {
	m_fields[index][i] = data[i];
      } else {
	m_fields[i][index] = data[i];
      }
    }
  }

  unsigned int m_size;
  list<Pair> m_empty_fields;
  vector<vector<Field> > m_fields;
};

ostream& operator<<(ostream& stream, const Grid& grid) {
  unsigned int n = grid.get_size();
  for (unsigned int i = 0; i < n; ++i) {
    stream << Line(grid.get_line(i, ROW)) << endl;
  }
  return stream;
}


#endif // __GRID_HH__
