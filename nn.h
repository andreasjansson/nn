#ifndef NN_H
#define NN_H

#include <random>
#include <assert.h>
#include <utility>
#include <vector>

using std::pair;
using std::vector;

typedef pair<vector<double>, vector<double>> TrainingExample;
typedef vector<double> TestExample;

inline double random_double(double min, double max)
{
  assert(max >= min);
  double random = ((double)rand()) / (double)RAND_MAX;
  double range = max - min;  
  return random * range + min;
}


#endif
