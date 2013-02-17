#ifndef NETWORK_H
#define NETWORK_H

#include <list>
#include <vector>
#include "neuron.h"

using std::list;
using std::vector;

typedef list<Neuron *> Layer;

class Network {

public:
  Network(vector<int> &);
  //Network(const Network &);
  void train(vector<double> &);
  double test(vector<double> &);

private:
  vector<Layer *> layers;

  void forward_propagation();
};

#endif
