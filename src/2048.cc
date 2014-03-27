#include <iostream>
#include <list>
#include <vector>

#include "grid.hh"

using namespace std;


MoveDirection get_move_direction(unsigned int i) 
{
  switch (i)
    {
    case 0:
      return LEFT;
    case 1:
      return RIGHT;
    case 2:
      return UP;
    default:
      return DOWN;
    }
}


unsigned int bot_play() {
  Grid grid(3);
  MoveDirection direction;
  unsigned int cnt = 0;
  vector<Pair> vec;  
  
  grid.fill_fields(2, 2);
  
  while (grid.is_locked() == false) {
    direction = get_move_direction(cnt);
    cnt = (cnt + 1) % 4;

    grid.move(direction, vec);
    grid.merge(direction, vec);
    grid.move(direction, vec);    
    grid.fill_fields(1, 2);
  }  

  cout << grid << endl << endl;

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
  
  bot_play();
  return 0;
}
