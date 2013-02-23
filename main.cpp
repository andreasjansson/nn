#include <list>
#include <tuple>
#include <vector>
#include <stdio.h>
#include "network.h"
#include "nn.h"

using std::list;
using std::vector;
using std::tuple;
using std::make_tuple;
using std::initializer_list;

int main(int argc, char **argv)
{
  vector<int> layer_sizes{2, 2, 1};
  Network network(layer_sizes);

  list<TrainingExample> training_examples{
    {{-1, -1}, {-1}},
    {{-1, 1}, {1}},
    {{1, -1}, {-1}},
    {{1, 1}, {1}}
  };

  network.train(training_examples, 4);

  list<TestExample> test_examples{
    {-1, -1},
    {-1, 1},
    {1, -1},
    {1, 1}
  };

  for(TestExample example : test_examples) {
    list<double> *result = network.test(example);
    printf("[ ");
    for(double x : example) {
      printf("%.0f ", x);
    }
    printf("] => ");
    printf("[ ");
    for(double x : *result) {
      printf("%.2f ", x);
    }
    printf("]\n");

    free(result);
  }
}
