#ifndef NETWORK_H
#define NETWORK_H

#include <list>
#include <vector>
#include "neuron.h"
#include "nn.h"

using std::list;
using std::vector;

typedef list<Neuron *> Layer;

class Network {

public:
  Network(vector<int> &);
  ~Network();
  //Network(const Network &);
  void train(const list<TrainingExample> &, int = 10);
  list<double> *test(const vector<double> &);

private:
  vector<Layer *> layers;
  double learning_rate;
  Layer *input_layer;
  Layer *output_layer;

  void forward_propagation();
  void back_propagation(const vector<double> &);
  void print_debugging();
};

#endif
