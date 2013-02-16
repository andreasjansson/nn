#ifndef NETWORK_H
#define NETWORK_H

#include <list>
#include "neuron.h"

using std::list;

class Network {

private:
  list<list<Neuron *>> layers;

public:
  void forward_propagation();
};

#endif
