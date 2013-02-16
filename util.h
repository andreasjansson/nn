#include <random>
#include <assert.h>

double random_double(double min, double max)
{
  assert(max >= min);
  double random = ((double)rand()) / (double)RAND_MAX;
  double range = max - min;  
  return random * range + min;
}
