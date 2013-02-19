#include <list>
#include <tuple>
#include <vector>
#include <stdio.h>
#include "network.h"

using std::list;
using std::vector;
using std::tuple;
using std::make_tuple;
using std::initializer_list;

int main(int argc, char **argv)
{
  vector<int> layer_sizes = {2, 2, 1};
  Network network(layer_sizes);

  network.train(vector<double>{0, 0}, vector<double>{0});
}
