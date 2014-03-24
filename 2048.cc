#include <iostream>
#include "grid.hh"

using namespace std;

int main(int argc, char** argv) {
  Field f(0);
  Field g(0);
  Field h(1);

  vector<Field*> fields;
  fields.push_back(&f);
  fields.push_back(&g);
  fields.push_back(&h);

  Line line(fields);
  cout << line << endl;
  vector<Pair> merges = line.merge(FRONT);
  vector<Pair> moves = line.move(FRONT);

  return 0;
}
