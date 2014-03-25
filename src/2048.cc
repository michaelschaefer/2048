#include <iostream>
#include <list>
#include <vector>

#include "grid.hh"

using namespace std;


int main(int argc, char** argv) {
  list<Pair> lst;
  vector<Pair> vec;

  Grid grid(4);
  grid.fill_fields(6, 2);
  cout << grid << endl << endl;

  grid.move(DOWN, vec);
  print_vector(vec);
  cout << endl << grid << endl;
  lst = grid.get_empty_fields();
  print_list(lst);
  cout << endl;

  return 0;
}
