#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "grid.hh"

using namespace std;


MoveDirection get_random_move_direction() {  
  int d = rand() % 4;  
  cout << d << endl;
  if (d == 0)
    return LEFT;
  else if (d == 1)
    return RIGHT;
  else if (d == 2)
    return UP;
  else
    return DOWN;
}


unsigned int bot_play() {
  Grid grid(4);
  MoveDirection direction;
  vector<Pair> vec;  
  
  grid.fill_fields(2, 2);

  while (grid.is_locked() == false) {
    direction = get_random_move_direction();    
    grid.move(direction, vec);
    grid.merge(direction, vec);
    grid.move(direction, vec);    
    grid.fill_fields(1, 2);
  }

  return 0;
}


int main(int argc, char** argv) {
  /*Grid grid(4);
  vector<Pair> vec;
  MoveDirection direction = DOWN;

  grid.fill_fields(6, 2);
  cout << grid << endl << endl;

  grid.move(direction, vec);
  grid.merge(direction, vec);
  grid.move(direction, vec);
  grid.fill_fields(1, 2);

  cout << grid << endl << endl;

  list<Pair> empty_fields = grid.get_empty_fields();
  for(list<Pair>::iterator iterator = empty_fields.begin(); iterator != empty_fields.end(); ++iterator) {
    cout << *iterator << ", ";
  }
  cout << endl;*/
  
  srand(time(0));
  bot_play();

  return 0;
}
