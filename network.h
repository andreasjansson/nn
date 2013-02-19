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
  ~Network();
  //Network(const Network &);
  void train(const vector<double> &, const vector<double> &, int = 10);
  double test(const vector<double> &);

private:
  vector<Layer *> layers;
  Layer *input_layer;
  Layer *output_layer;

  void forward_propagation();
  void back_propagation(const vector<double> &);
};

#endif
