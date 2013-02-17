#include <list>
#include <vector>
#include <stdio.h>
#include "network.h"

using std::list;
using std::vector;

int main(int argc, char **argv)
{
  vector<int> layer_sizes = {2, 2, 1};
  Network network(layer_sizes);

  list<vector<double>> examples{
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1}
  };

  for(auto example : examples) {
    network.train(example);
  }
}
